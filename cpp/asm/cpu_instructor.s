	.file	"cpu_instructor.cpp"
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.text
	.globl	_Z11add_a_and_bii
	.type	_Z11add_a_and_bii, @function
_Z11add_a_and_bii:
.LFB1018:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1018:
	.size	_Z11add_a_and_bii, .-_Z11add_a_and_bii
	.globl	_Z11another_foov
	.type	_Z11another_foov, @function
_Z11another_foov:
.LFB1019:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1019:
	.size	_Z11another_foov, .-_Z11another_foov
	.globl	namea
	.section	.rodata
.LC0:
	.string	"hello"
	.data
	.align 8
	.type	namea, @object
	.size	namea, 8
namea:
	.quad	.LC0
	.globl	nameb
	.section	.rodata
.LC1:
	.string	"bbbbb"
	.data
	.align 8
	.type	nameb, @object
	.size	nameb, 8
nameb:
	.quad	.LC1
	.globl	age
	.bss
	.align 4
	.type	age, @object
	.size	age, 4
age:
	.zero	4
	.globl	level
	.data
	.align 4
	.type	level, @object
	.size	level, 4
level:
	.long	100
	.section	.rodata
.LC2:
	.string	"%d"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1020:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$10000, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	$3, %esi
	movl	$2, %edi
	call	_Z11add_a_and_bii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1020:
	.size	main, .-main
	.type	_Z41__static_initialization_and_destruction_0ii, @function
_Z41__static_initialization_and_destruction_0ii:
.LFB1021:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	cmpl	$1, -4(%rbp)
	jne	.L6
	cmpl	$65535, -8(%rbp)
	jne	.L6
	movl	$_ZStL8__ioinit, %edi
	call	_ZNSt8ios_base4InitC1Ev
	movl	$__dso_handle, %edx
	movl	$_ZStL8__ioinit, %esi
	movl	$_ZNSt8ios_base4InitD1Ev, %edi
	call	__cxa_atexit
.L6:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1021:
	.size	_Z41__static_initialization_and_destruction_0ii, .-_Z41__static_initialization_and_destruction_0ii
	.type	_GLOBAL__sub_I__Z11add_a_and_bii, @function
_GLOBAL__sub_I__Z11add_a_and_bii:
.LFB1022:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$65535, %esi
	movl	$1, %edi
	call	_Z41__static_initialization_and_destruction_0ii
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1022:
	.size	_GLOBAL__sub_I__Z11add_a_and_bii, .-_GLOBAL__sub_I__Z11add_a_and_bii
	.section	.ctors,"aw",@progbits
	.align 8
	.quad	_GLOBAL__sub_I__Z11add_a_and_bii
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 4.9.2"
	.section	.note.GNU-stack,"",@progbits
