Kommentierung: #

    e.g. #  Diese Zeile ist ein Kommentar

Adresse: $

    e.g. $1 --> Register 1

Arithmetic Operations:

    Addition: ADD, ADDI (2 Arguments)
        ADD $1, $1, $2 --> $1 = $1 + $2
        ADDI $1, $1, 5 --> $1 = $1 + 5
    
    Subtraction: SUB, SUBI (2 Arguments)
        SUB $1, $1, $2 --> $1 = $1 - $2
        SUBI $1, $1, 5 --> $1 = $1 - 5

    Multiplication: MUL, MULI (2 Arguments)
        MUL $1, $1, $2 --> $1 = $1 * $2
        MULI $1, $1, 5 --> $1 = $1 * 5

    Division: DIV, DIVI (2 Arguments)
        DIV $1, $1, $2 --> $1 = $1 / $2
        DIVI $1, $1, 5 --> $1 = $1 / 5

    Increment & Decrement: INCR, DECR (1 Argument)
        INCR $1 --> $1 = $1 + 1
        DECR $1 --> $1 = $1 - 1       

Input & Output:

    Input: INPUT (1 Argument)
        INPUT $1 --> takes input from user and save it in register 1

    Output: SHOW (infinite Argument)
        SHOW "Value of 1. Register is ", $1 

Assignment Operator: SET (2 Argumnets)

    SET $1, 10 --> $1 = 10

Loops:

    Loop name:
        e.g. BEGIN --> it can be any word except defined operators(e.g. ADD, INPUT)
    
    Jump Statement: JMP (1 argument)
        JMP BEGIN --> jump BEGIN
    
    Conditional Statements: JLT, JGT (3 Argument)
        e.g. JLT BEGIN, $1, $2 --> jump BEGIN if value of $1 is less than $2
        e.g. JGT BEGIN, $1, 10 --> jump BEGIN if value of $1 is greater than 10

System Commands: SYS (1 argument -> System command as String)
    e.g. SYS "mkdir Photos"

Exit: END
    e.g. END --> terminates Program
