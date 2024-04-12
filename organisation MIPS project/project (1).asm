######## begin of data segment #########
.data
#####  messages for start program ###
start: .asciiz "\nHello, Enter number from 1 t0 6 for string operation or 7 t0 exitt\n"
choices: .asciiz " 1- string length \n 2- search \n 3-reverse \n 4- UpperCase \n 5- index of \n 6- substring \n"
Wrong: .asciiz "Wrong choice Try Again!"
###### String which we used ##########
str: .asciiz " "  #string 

msg: .asciiz "\nEnter String:"
msg_search: .asciiz "\nfound: "
msg_search2: .asciiz "\ncharcter:"
msg_length: .asciiz  "\nlength of string = "
msg_revers: .asciiz "\nReverse String: "
msg_indexC: .asciiz "\nEnter Character:"
msg_index: .asciiz "\nindex of characte:"
msg_indexP: .asciiz "\nEnter Start Position: "
msg_SUBE: .asciiz "\nExeciption Error"
msg_SUBI: .asciiz "\nEnter intial index:"
msg_SUBF: .asciiz "Enter end index:"
newline: .asciiz "\n"

######## BEGIN OF CODE #######
.text 
j Main

############# procedure of string length #################
##### $a0 -> string
strLength: 
# save register $s0 , $s1 in stack
addi $sp , $sp , -8 
sw $s0 , 0($sp)
sw $s1 , 4($sp)

add $s0 , $0 ,$0    #i=0  intialize index of string
add $s1 , $0 , $0  #length = 0  intialize variable to save length

while1:               #loop  
add $t0 , $s0 , $a0       #str1[i] 
lbu $t1, 0($t0)           # load character in str[i] in $t1
beqz $t1, exit1           # check if str[i] == '\0' if $t1 = 0 -> exit , else 
addi $s0 , $s0 ,1         # i++  
addi $s1, $s1, 1          # length ++  
j while1                   
 exit1:    #exit if condition true
add $v1 , $s1 , -1   #retrun length 
# load values from stack 
lw $s0 , 0($sp)
lw $s1 , 4($sp)
addi $sp , $sp , 8
jr $ra    #end

########## procedure of search #################
#$a1 = character , $a0 = string
search:
# save value in $ra in stack 
addi $sp , $sp , -4
sw $ra , 0($sp)

add $s0 , $0 ,$0   # i=0 , intialize index of string
add $s1 , $0 , $0  # founde =0 ; intialize variable indicato to number of repetition of char in string 
jal strLength      # call procedure to know length 
for1: 
slt $t0 , $s0 , $v1   # if i < length -> $t0 =1 , else  -> $t0=0
beqz $t0 , exit2      # if $t0 =0 -> exit , else 
add $t0 , $s0 , $a0   #str[i]
lbu $t1 , 0($t0)      #load character
addi $s0 , $s0 ,1     # i++ 
bne $a1 , $t1 , for1   #if ch != str[i] -> loop 
addi $s1 , $s1 , 1     #found++
j for1       # jump untill i > length

exit2:
move $v1 , $s1        # return 0 -> indicat to this char not found in string
lw $ra , 0($sp)
addi $sp , $sp , 4
jr $ra  #end
 
###################### reverse procedure ################# ###############
#### $a1 -> string
reverse:
addi $sp , $sp , -8
sw  $ra , 0($sp)
jal strLength      # call procedure to know length of string $v1 -> length
While2:      #loop
addi $t0 , $v1 ,-1  # length-- ; save it in $t2
add $t1 , $a1 , $t0  #str[length-1] -> last char in string 
lbu $t2 , 0($t1)     # load char in $t3
beqz $t2 , exit3    # if char = 0 -> exit  "End of string"
li $v0 , 11          # load in $v0 , 11 to print char
la $a0 , 0($t2)      # load add of char 
syscall              #print 
addi $v1 , $v1 , -1  #length-=length -> change length 
j While2  # jump to loop until end 
exit3:
lw $ra , 0($sp)
addi $sp , $sp ,8
jr $ra #end

################### indexOf #####################
#### $a3 -> start position , $a2-> character , $a0 -> string
indexOf:
addi $sp , $sp , -4
sw $ra , 0($sp)

add $s1 , $0 , $0       #i=0 ; intialize index
jal strLength           # call procedure to knoe length , $v1 -> length
blt  $a3 , $v1 , else2    # posi < length -> else  
addi $v1 , $0 , -1         #  return -1 "out of range"
lw $ra , 0($sp)
addi $sp ,$sp ,4
jr $ra              #end procedure 
else2:
bgtz  $a3 , case      #posi >  0 -> for
case:
move $s0 , $a3 
j for2
move $s0 , $0          #pos < 0 -> pos =0
for2:             ### begining of search 
bgt $s0 , $v1 , exit4 # pos > length -> exit       
add $t0 , $a0 , $s0   #str[i]
lbu $t1 , 0($t0)      #load char in $t1
addi $s0 , $s0 ,1     # pos++
bne $a2 , $t1 , for2   # chaeck if char != str[i] , jump to loop
addi $s1 , $s1 , 1     # if char == str[i] ,id++
addi $s0 , $s0 ,-1     # pos--;
exit4:
bne $s1 , $0 , else3   #if id !=0 -> else
addi $v1 , $0 , -1         # i==0 -> return value =-1 "not found"
lw $ra , 0($sp)
addi $sp , $sp ,4
jr $ra  #end 
else3:  # i= number
move $v1 , $s0 #return number 
lw $ra , 0($sp)
addi $sp , $sp ,4
jr $ra #end
############### SubString ######################
#### $a1 -> start , $a2 -> end , $a3 -> string
subString:
addi $sp , $sp , -4
sw $ra , 0($sp) 
#case1
bltz  $a1 , exit5        # if start < 0 ,branch exit5
#case2
blt  $a2 , $a1 , exit5   #if end < start ,branch exit5
jal strLength            ###length=v1    
#case3   
bgt  $a2 , $v1, exit5    #if end > length,branch exit5       
while3:                  #loop 
beq $a1 , $a2 , exit6    # if start == end -> exit6
print:                   #print char
add $t0 , $a1 , $a3      #str[start]
lbu $t1 , 0($t0)         #load char in t1
li $v0 , 11              #print char    
la $a0 ,0($t1)
syscall
addi $a1 , $a1 , 1       #start++
j while3 #jump to loop until start == end
exit5:
li $v0 , 4
la $a0 , msg_SUBE        ##msg_SUBE: .asciiz "\nExeciption Error"
syscall
lw $ra , 0($sp)
addi $sp , $sp ,4
jr $ra   # end and go to main
exit6:
lw $ra , 0($sp)
addi $sp , $sp ,4
jr $ra   # end and go to main
################## UPPerCase #################
##### $a1 -> string
UpperCase:    # $a1 -> string
addi $sp, $sp ,-4
sw $ra , 0($sp)

jal strLength      #call length procedur to know length , $v1 = length
add $s0 , $0 ,$0   # i=0 , initialize index
for3: #loop 
bgt $s0 , $v1 , exit51  # i < length $t0=1 , i>length $t0 =      # if $t0==0 -> exit 
add $t0 , $s0 ,$a1       # $t0==1 , str[i]
lbu $t1 , 0($t0)     # load char
beq $t1 , 32 , space
slti $t2 , $t1 , 97     # str[i] < 32 -> capital ,$t2=1  notbranch ,  $t2= 0 ,branch -> small
bnez $t2 , else4      #if $t2 != 0 -> else , capital 
addi $t1 , $t1 ,-32   #ascii code for char - 32 -> char in uppercase
print2:  #print 
li $v0 , 11
la $a0 ,0($t1)
syscall  #print char
addi $s0 , $s0 , 1  #i++
j for3
else4:  # $t2 !=0 , char in upper
  j print2
 space:
 j print2
exit51:   
lw $ra , 0($sp)
addi $sp ,$sp ,4
jr $ra  #end
###########################  MAIN EXECUTION  #########################
Main:
# loop to begin system 
li $v0 , 4 
la $a0 , msg  
syscall       # print -> Enter String:
li $v0 , 8
la $a0 , str
la $a1 , 20
syscall  #input string
do:
li $v0 , 4
la $a0 , start
syscall  #print message -> "Hello, Enter number from 1 t0 6 for string operation or 7 t0 exit"
li $v0 , 4
la $a0 , choices
syscall   #print message to visiualize choices of operation
          #1- string length  2- search  3-reverse  4- index of  5- substring  6- UpperCase
li $v0 , 5
syscall    # user input choice
beq $v0 , 1 , p1 
beq $v0 , 2 , p2
beq $v0 , 3 , p3
beq $v0 , 4 , p4
beq $v0 , 5 , p5
beq $v0 , 6 , p6
beq $v0 , 7 , p7

li $v0 , 4
la $a0 , Wrong
syscall   #print ->  "Wrong choice Try Again!"
j do       #jump to do
############### find length ######################
p1:
la $a0 , str  #load string address 
jal strLength  # jump to finction 
li $v0 ,4
la $a0 , msg_length 
syscall  #print -> length of string
li $v0 , 1
move $a0 , $v1 #move length in $a0 
syscall #print lenth
j do #jump to do
############ search in string ####################### 
p2:
li $v0 , 4
la $a0 , msg_search2 #print -> charcter:
syscall
li $v0 , 12
syscall  #user input character
move $a1 , $v0  #save character in $a1
la $a0, str     #save add. of string $a0
jal search  #jump to func.
li $v0 , 4
la $a0 , msg_search
syscall  #print found:
#print number 0 : not found , any number : found and number indicate to The number of repetitions
li $v0 , 1
move $a0 , $v1
syscall #print number of repetition 
j do  #jump to do 
########### reverse string ################
p3:
li $v0 , 4
la $a0 , msg_revers
syscall  #print Reverse String:
la $a0 , str
move $a1 , $a0 #save string add. in $a0
jal reverse  #jump to func.
j do  #jump to do
########### indexOf ################
p5:
li $v0 , 4
la $a0 , msg_indexC
syscall 
li $v0 , 12
syscall
move $a2 , $v0 
li $v0 , 4
la $a0 , msg_indexP
syscall
li $v0 , 5
syscall
move $a3 , $v0 
la $a0 , str
jal indexOf
li $v0 , 4
la $a0 ,  msg_index
syscall
li $v0 , 1
move $a0 , $v1
syscall
j do
################ SubString ################
p6:
li $v0 ,4
la $a0 , msg_SUBI
syscall
li $v0 , 5
syscall
move $a1 , $v0
li $v0 ,4
la $a0 , msg_SUBF
syscall
li $v0 , 5
syscall
move $a2 , $v0
la $a0 , str
move $a3 , $a0
jal subString
li $v0 , 4
la $a0 , newline
syscall
j do
############### UpperCase #################
p4:
la $a0 , str
move $a1 , $a0
jal UpperCase
j do
############ End Program #############
p7:
j EndProgram
EndProgram:
li $v0 , 10
syscall
  
