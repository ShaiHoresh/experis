	.file	"thread.c"
	.comm	g_val,4,4
	.section	.rodata
.LC0:
	.string	"%ld, %d\n"
	.text
	.globl	PrintFunc
	.type	PrintFunc, @function
PrintFunc:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	8(%ebp), %eax
	movl	%eax, -28(%ebp)
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	movl	$5, -16(%ebp)
	movl	-28(%ebp), %eax
	movl	%eax, -20(%ebp)
	movl	-20(%ebp), %eax
	subl	$4, %esp
	leal	-20(%ebp), %edx
	pushl	%edx
	pushl	%eax
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	subl	$12, %esp
	pushl	$0
	call	pthread_exit
	.cfi_endproc
.LFE0:
	.size	PrintFunc, .-PrintFunc
	.section	.rodata
.LC1:
	.string	"succeed %d threads\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$4036, %esp
	movl	%ecx, %eax
	movl	4(%eax), %eax
	movl	%eax, -4028(%ebp)
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	movl	$0, -4020(%ebp)
.L6:
	movl	-4020(%ebp), %eax
	leal	-4012(%ebp), %edx
	movl	-4020(%ebp), %ecx
	sall	$2, %ecx
	addl	%ecx, %edx
	pushl	%eax
	pushl	$PrintFunc
	pushl	$0
	pushl	%edx
	call	pthread_create
	addl	$16, %esp
	movl	%eax, -4016(%ebp)
	addl	$1, -4020(%ebp)
	cmpl	$0, -4016(%ebp)
	je	.L6
	subl	$8, %esp
	pushl	-4020(%ebp)
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	nop
	movl	$0, -4020(%ebp)
	jmp	.L7
.L8:
	movl	-4020(%ebp), %eax
	movl	-4012(%ebp,%eax,4), %eax
	subl	$8, %esp
	pushl	$0
	pushl	%eax
	call	pthread_join
	addl	$16, %esp
	addl	$1, -4020(%ebp)
.L7:
	cmpl	$9, -4020(%ebp)
	jbe	.L8
	subl	$12, %esp
	pushl	$0
	call	pthread_exit
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
