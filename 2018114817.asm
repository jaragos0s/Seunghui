.globl main
.data
buf : .space 512
msg1: .asciz "Expression: "
msg2: .asciz "Received: "
space: .asciz "\n"
.text
main:
	la a0, msg1
	li a7, 4 # print "Expression: "
	ecall
	
	la a0, buf
	li a1, 512
	li a7, 8 # read a string from the console
	ecall
	la a1, buf

 	la a0, msg2
	li a7, 4 # print "Received:"
	ecall

	la a0, buf
	li a7, 4 # print the string to the console
	ecall
	
	mv t0, a0 
	
	addi t1, zero, 43 # +
	addi t2, zero, 45 # -
	addi t3, zero, 47 # /
	addi t4, zero, 120 # x
	addi t5, zero, 61 # =
	addi s4, zero, 48
	addi s3, zero, 57
	addi s1, zero, 10
	addi s6, zero, 0
	lb a0, 0(a0)

firstop: 
	lb a0, 0(t0)
	ble a0, s4, loop #if input < 48 or
	bgt a0, s3, loop #if input > 57 , go to loop
	
	addi t0, t0, 1
	
	mul s7, s7, s1 #result = result * 10
	sub s0, a0, s4 #s0 = input - 48
	add s7, s7, s0 #result = result + s0

	beqz zero, firstop
	
loop:  # s7 : result, s6 : operator, s5 : operand, s4 : 48 s3 : 57, s2 : temp, s1 : 10
	
	lb a0, 0(t0)
	addi t0, t0, 1 # char만큼씩 이동 
	
	beqz a0, exit
       
       bge a0, s4, Compare #if input >= 48
       ble a0, s4, Operator # if input < 48
       

       bnez a0, loop
    
Compare: 
	ble a0, s3, MakeOperand #if input <= 57
	bge a0, s3, Operator	# else, it is operator
MakeOperand:

	mul s5, s5, s1 # operand = operand * 10
	sub s0, a0, s4 # input = input - 48 (ascii)
	add s5, s0, s5 # operand = opeand * 10 + (input - 48)
	
	beqz zero, loop
Operator:

	beq s6, t1, plus # operator : +
	beq s6, t2, minus # operator : -
	beq s6, t3, division # operator : /
	beq s6, t4, multiple # operator : x
	addi s6, a0, 0 	# operator = input
	beqz zero, loop	
	
ToPrint:
	addi s5, zero, 0 	#initialize operand
	addi s6, a0, 0 	#operator = input
	jal ra,Print

	beq s6, t5, exit
	beqz zero, loop

Print:	
	mv a0, s7		
	li a7, 1		#print value
	ecall
	
	la a0, space
	li a7, 4
	ecall
	
	jalr zero, 0(ra)
	
plus: 
	add s7, s7, s5
	beqz zero, ToPrint
minus: 
	sub s7, s7, s5
	beqz zero, ToPrint
division: 
	div s7, s7, s5
	beqz zero, ToPrint
multiple: 
	mul s7, s7, s5
	beqz zero, ToPrint

exit: 
