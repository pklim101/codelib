import scala.util.matching.Regex

object HelloWorld{
    def main(args: Array[String]){
        val pattern = "scala".r
        val str = "scala is scalable and cool"
        println(pattern findFirstIn str)
    }
}
