	.file	"MyStrlen.c"
	.text
	.globl	MyStrlenIt
	.type	MyStrlenIt, @function
MyStrlenIt:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	$0, -4(%ebp)
	jmp	.L2
.L3:
	addl	$1, -4(%ebp)
.L2:
	movl	-4(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	.L3
	movl	-4(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	MyStrlenIt, .-MyStrlenIt
	.globl	MyStrlenRec
	.type	MyStrlenRec, @function
MyStrlenRec:
.LFB1:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	12(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	.L6
	movl	12(%ebp), %eax
	jmp	.L5
.L6:
	addl	$1, 12(%ebp)
	subl	$8, %esp
	pushl	12(%ebp)
	pushl	8(%ebp)
	call	MyStrlenRec
	addl	$16, %esp
.L5:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE1:
	.size	MyStrlenRec, .-MyStrlenRec
	.section	.rodata
.LC0:
	.string	"shalom al Israel"
.LC1:
	.string	"%d\n"
.LC2:
	.string	"%d, %c\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
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
	subl	$20, %esp
	movl	$.LC0, -16(%ebp)
	movb	$53, -17(%ebp)
	movsbl	-17(%ebp), %eax
	movl	%eax, -12(%ebp)
	pushl	-16(%ebp)
	call	MyStrlenIt
	addl	$4, %esp
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$0
	pushl	-16(%ebp)
	call	MyStrlenRec
	addl	$16, %esp
	subl	$8, %esp
	pushl	%eax
	pushl	$.LC1
	call	printf
	addl	$16, %esp
	movsbl	-17(%ebp), %eax
	subl	$4, %esp
	pushl	%eax
	pushl	-12(%ebp)
	pushl	$.LC2
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
