#!/bin/awk -f
BEGIN{
        IGNORECASE=1;
        "/sbin/ifconfig eth1 |grep \"inet addr\"| cut -f 2 -d \":\"|cut -f 1 -d \" \""|getline proxyIP;
        "/sbin/ifconfig eth0 |grep \"inet addr\"| cut -f 2 -d \":\"|cut -f 1 -d \" \""|getline localIP;
        "/bin/hostname |  egrep -o '(bjcc|bjdt|bjsc|gzst|shgt|shjc|shyc2|shbt|zwt|zzzc|zzbc)'"|getline localIdc;
        "date +%Y%m%d%H%M -d \"-1 mins\""|getline timeToDB

        ##入库api
        insertAPI="http://123.125.73.218/logToData_test.php"
        
        ##入库时间
        timeToDB=sprintf("%s00",timeToDB);
        #urlHttpcodeCount[url,proxyCode,localIP]        proxy访问量
        #urlHttpcodeTime[url,proxyCode,localIP]         proxy访问总时间
        #appHttpcodeCount[url,appIp,appCode]            app访问量
        #appHttpLagTotal[url,appIp,appCode]             app访问总时间
        #route[front_ip,localIP]                        整个数据流路由表
        "> 123.txt"|getline
}
!/robots.txt/ && !/mob.*.360.cn/ && !/webscan/{
        #统计proxy信息
        #awk '{split($0,arr,"//");split(arr[2],arr1," ");split(arr1[1],arr2,"?");;print arr2[1]}'
        split($0,arrUrl1,"//");
        split(arrUrl1[2],arrUrl2," ");
        split(arrUrl2[1],arrUrl3,"?");
        split($0,arr2,"\"");
        url=arrUrl3[1];
        gsub("/$","",url);
        arr2Count=length(arr2);
        proxyCodeTemp=arr2[arr2Count-8];
        split(proxyCodeTemp,proxyCodeTempArr," ");;
        proxyCode=proxyCodeTempArr[1];
        bodySize=proxyCodeTempArr[2];
        if(bodySize<500){
            adSucc= "n";
        }else{
            adSucc= "y";
        }
        urlHttpcodeCount[url,proxyCode,localIP,adSucc]++;
        if(!match(proxyCode,"2[0-9][0-9]|3[0-9][0-9]")){
                print $0 >> "123.txt"
                lineCount++;
        }
        
        num=split($0,arr3,"[");
        ####提取proxy返回时间
        tmpNum=split(arr3[num-2],tmp," ");
        proxyTime=tmp[tmpNum];
        gsub("\"","",proxyTime);
        urlHttpcodeTime[url,proxyCode,localIP,adSucc]+=proxyTime;
	#将response time按url等进行分类存储
        number=urlHttpcodeCount[url,proxyCode,localIP,adSucc];
        responseTime[url,proxyCode,number]=proxyTime;
}
END{
        #计算总数、成功率，用于zabbix
        for(one in urlHttpcodeCount){
                split(one,tmpArr,SUBSEP);
                url=tmpArr[1];
                httpCode=tmpArr[2];
                count=urlHttpcodeCount[one];
                if(match(httpCode,"2[0-9][0-9]|3[0-9][0-9]")){
                        sucCount[url]+=count;#存url成功数
                }
                urlCount[url]+=count;#存url总数
        }
        for(one in urlCount){
                if(sucCount[one]==""){
                        sucCount[one]=0;
                }
                proxyRate=sucCount[one]*100/urlCount[one];
                #"/usr/local/zabbix/bin/zabbix_sender -z 10.108.68.121 -s " localIP " -k " one "-pv -o " urlCount[one]|getline;
                #"/usr/local/zabbix/bin/zabbix_sender -z 10.108.68.121 -s " localIP " -k " one "-rate -o " proxyRate|getline;
                #printf("url:%-28ssuc:%-10stotal:%-10srate:%-10.3fend\n",one,sucCount[one],urlCount[one],sucCount[one]/urlCount[one]*100);

        }
        for(one in urlHttpcodeCount){
                split(one,tmpArr,SUBSEP);
                url=tmpArr[1];
                httpCode=tmpArr[2];
                count=urlHttpcodeCount[one];
                avg_time=urlHttpcodeTime[one]/count;
                total_time=urlHttpcodeTime[one];
                total_all=urlCount[url];
		#计算response time在99和50比例时候的值
                delete tmp;
                delete sortRt;
                for (i=1;i<= count;i++){
                        tmp[i] = responseTime[url,httpCode,i];
                }
                len=asort(tmp,sortRt);
                if (len == 1) {
                        rt_99_index =1;
                        rt_50_index =1;
                } else {
                        rt_99_index =int(len*0.99);
                        rt_50_index =int(len*0.5);
                }
                if(tmpArr[4]=="y"){
                    adSuccSum = count;
                }else{
                    adSuccSum = 0;
                }
                #printf("url:%-48shttp-code:%-5scount:%-10stotal_all:%-10dlag:%-5s\n",url,httpCode,urlHttpcodeCount[one],total_all,urlHttpcodeTime[one]/count);
                #在此处入库字段:timeToDB url proxy localIP httpCode count urlHttpcodeTime[one]/count urlHttpcodeTime[one]
                #"curl -X POST -d \"time="timeToDB"&url="url"&action=front&ip="localIP"&http_code="httpCode"&total="count"&avg_time="avg_time"&total_time="total_time"&total_all="total_all"\" http://123.125.73.218/frontToData.php > /dev/null 2>&1"|getline
               # "curl \"http://123.125.73.218/frontToDataIdc.php?time="timeToDB"&url="url"&action=front&idc="localIdc"&ip="localIP"&http_code="httpCode"&total="count"&avg_time="avg_time"&total_time="total_time"&total_all="total_all"\" > /dev/null 2>&1"|getline
                "curl \"http://10.172.171.234/frontToDataIdc.php?time="timeToDB"&url="url"&action=front&idc="localIdc"&ip="localIP"&http_code="httpCode"&total="count"&avg_time="avg_time"&total_time="total_time"&total_all="total_all"\" > /dev/null 2>&1"|getline
                "curl -H \"Host: wyz.monitor.com\" \"http://10.172.171.234/frontToDataIdc.php?time="timeToDB"&url="url"&action=front&idc="localIdc"&ip="localIP"&http_code="httpCode"&total="count"&avg_time="avg_time"&total_time="total_time"&total_all="total_all"&rt_99="sortRt[rt_99_index]"&rt_50="sortRt[rt_50_index]"&adsucc="adSuccSum"\" > /dev/null 2>&1"|getline
        }
        if(lineCount>0){
                close("123.txt");
                #"curl -F \"file=@123.txt\" -F \"srcAddr="localIP"\" -F \"time="timeToDB"\" -F \"logType=front\" -F \"lineCount="lineCount"\"  http://123.125.73.218/storeErrLog.php > /dev/null 2>&1" |getline
        }
}
