from re import A
import ply.lex as lex
import ply.yacc as yacc
import sys

p1 = 1234577
p2 = 1234576

tokens = [
    'NUM',
    'ADD',
    'MINUS',
    'MUL',
    'DIV',
    'MOD',
    'POW',
    'LT_BR',
    'RT_BR',
    'EOL',
    'ERROR',
    'COMMENT',
    'EXPONENT',
]

t_ADD = r'\+'
t_MINUS = r'\-'
t_MUL = r'\*'
t_DIV = r'\/'
t_MOD = r'\%'
t_POW = r'\^'
t_LT_BR = r'\('
t_RT_BR = r'\)'
t_EOL = r'\n'
t_ignore = ' \t'
t_ignore_COMMENT = r'^[#].*\n'

def t_NUM(t):
    r'\d+'
    t.value = int(t.value)
    return t

def t_error(t):
     t.lexer.skip(1)

lexer = lex.lex()

precedence = (
    ('left', 'ADD', 'MINUS'),
    ('left', 'MUL', 'DIV'),
    ('nonassoc', 'POW')
)


def fix(x, P):
    x = int(x)
    if x < 0:
        return int(P - abs(x) % P)
    else:
        return int(x % P)

def inverse(x, P):
    x = int(x)
    i = int(1)
    while i < P:
        if (i * x) % P == 1:
            return int(i)
        i += 1
    global error
    error = 1
    print("There is no inverse for " + str(x) + "\n")
    return -1

def add(x, y, P):
    x = int(x)
    y = int(y)
    return int(fix(x + y, P))

def sub(x, y, P):
    x = int(x)
    y = int(y)
    return int(fix(x - y, P))

def mul(x, y, P):
    x = int(x)
    y = int(y)
    return int(fix(x*y, P))

def divide(x, y, P):
    x = int(x)
    y = int(y)
    return int(fix(x * inverse(y, P), P))

def mod(x, y, P):
    x = int(x)
    y = int(y)
    return int(fix(x % y, P))

def power(x, y, P):
    x = int(x)
    y = int(y)
    ans = 1
    i = 0
    while i < y:
        ans *= x
        ans %= P
        i += 1
    return int(fix(ans, P))

stack = []
error = 0

def p_ex2(p):
    '''
    ex2 : exp
         | empty
    '''
    if(type(p[1]) == type(int(1))):
        global stack
        global error
        postfix = str("")
        c = "~"
        for i in stack:
            cl = c
            c = str(i)
            if(c == cl and c == "^"):
                error = 1
                print("power stacking not allowed\n")
                
        if(error == 0):
            for i in stack:
                postfix += str(i)
                postfix += " "
            print(postfix)
            print("=", p[1], "\n")
    elif (type(p[1]) == type(str(""))):
        print("comment")
    stack = []
    error = 0

def p_error(p):
    print("Syntax error\n")
    global stack
    global error
    stack = []

def p_empty(p):
    '''
    empty :
    '''
    p[0] = None

def p_factor(p):
    '''
    exp  :    NUM                         
            | MINUS NUM                 
            | MINUS LT_BR exp RT_BR     
            | LT_BR exp RT_BR           
    '''

    if(len(p) == 2):
        p[0] = fix(p[1], p1)
        stack.append(fix(p[1], p1))
    
    elif(len(p) == 3):
        p[0] = fix(-p[2], p1)
        stack.append(fix(-p[2], p1))

    elif (len(p) == 4):
        p[0] = fix(p[2], p1)

    elif(len(p) == 5):
        p[0] = fix(-p[3], p1)
        stack.append("~")

def p_expADD(p):
    '''
    exp : exp ADD exp
    '''
    global stack
    
    p[0] = add(p[1], p[3], p1)
    stack.append("+")
    
def p_expMINUS(p):
    '''
    exp : exp MINUS exp 
    '''

    p[0] = sub(p[1], p[3], p1)
    stack.append("-")

def p_expPOW(p):
    '''
    exp : exp POW exponent
    '''
    global stack
    
    p[0] = power(p[1], p[3], p1)
    stack.append("^")

def p_expMUL(p):
    '''
    exp : exp MUL exp
    '''
    global stack
    p[0] = mul(p[1], p[3], p1)
    stack.append("*")

def p_expDIV(p):
    '''
    exp : exp DIV exp
    '''
    global stack
    global error
    if(p[3] == 0):
        if(error == 0):
            error = 1
            print("Division by zero")
        p[0] = 0
    else:
        p[0] = divide(p[1], p[3], p1)
        stack.append("/")

def p_factorexponent(p):
    '''
    exponent    : NUM                         
                | MINUS NUM                 
                | MINUS LT_BR exponent RT_BR     
                | LT_BR exponent RT_BR           
    '''

    if(len(p) == 2):
        p[0] = fix(p[1], p2)
        stack.append(fix(p[1], p2))
    
    elif(len(p) == 3):
        p[0] = fix(-p[2], p2)
        stack.append(fix(-p[2], p2))

    elif (len(p) == 4):
        p[0] = fix(p[2], p2)

    elif(len(p) == 5):
        p[0] = fix(-p[3], p2)
        stack.append("~")

def p_expADDexponent(p):
    '''
    exponent : exponent ADD exponent
    '''
    global stack
    
    p[0] = add(p[1], p[3], p2)
    stack.append("+")

def p_expMINUSexponent(p):
    '''
    exponent : exponent MINUS exponent 
    '''
    p[0] = sub(p[1], p[3], p2)
    stack.append("-")

def p_expMULexponent(p):
    '''
    exponent : exponent MUL exponent
    '''
    global stack
    p[0] = mul(p[1], p[3], p2)
    stack.append("*")

def p_expDIVexponent(p):
    '''
    exponent : exponent DIV exponent
    '''
    global stack
    global error
    if(p[3] == 0):
        if(error == 0):
            error = 1
            print("Division by zero")
        p[0] = 0
    else:
        p[0] = divide(p[1], p[3], p2)
        stack.append("/")

parser = yacc.yacc()

while True:
    try:
        s = input('')
    except EOFError:
        break
    parser.parse(s)

print(stack)