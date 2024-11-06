import numpy as np

# Node Classes

# Base Expression
class expression:
    def __str__():
        return "EXPRESSION"

    def diff():
        return "(expression value, expression derivative)"

# Base Expression Types
    
class Un_Op(expression):
    def __init__(self, a):
        self.a = a
    def __str__(self):
        return "[UNARY OP]"

class Bi_Op (expression):
    def __init__(self, a, b):
        self.a = a
        self.b = b
    def __str__(self):
        return "[BINARY OP]"
    
# Usable Expression Types

# Constants
class Const_Exp(expression):
    def __init__(self, val):
        self.value = val
    def __str__(self):
        return str(self.value)
    def diff(self):
        return (self.value, 0)

# Variables  
class Var_Exp(expression):
    def __init__(self, name = "x", value = None):
        self.name = name
        self.value = value
        return
    def __str__(self):
        return self.name
    def diff(self):
        return (self.value, 1)
    
# Unary Operations
class Sin_Op(Un_Op):
    def __str__(self):
        return f"sin({str(self.a)})"
    def diff(self):
        a_val, a_prime = self.a.diff()
        f_prime = np.cos(a_val) * a_prime
        return (np.sin(a_val), f_prime)
    
class Cos_Op(Un_Op):
    def diff(self):
        a_val, a_prime = self.a.diff()
        f_prime = -np.sin(a_val) * a_prime
        return (np.cos(a_val), f_prime)
    def __str__(self):
        return f"cos({str(self.a)})"
    
class Log_Op(Un_Op):
    def diff(self):
        a_val, a_prime = self.a.diff()
        f_prime = (1/a_val) * a_prime
        return (np.log(a_val), f_prime)   
    def __str__(self):
        return f"ln({str(self.a)})"
    
class Exp_Op(Un_Op):
    def diff(self):
        a_val, a_prime = self.a.diff()
        f_prime = np.exp(a_val) * a_prime
        return (np.exp(a_val), f_prime)
    def __str__(self):
        return f"exp({str(self.a)})"

# Binary Operations
class Add_Op(Bi_Op):
    def diff(self):
        a_val, a_prime = self.a.diff()
        b_val, b_prime = self.b.diff()
        return (a_val + b_val,  a_prime + b_prime)
    def __str__(self):
        return f"({str(self.a)} + {str(self.b)})"

class Sub_Op(Bi_Op):
    def diff(self):
        a_val, a_prime = self.a.diff()
        b_val, b_prime = self.b.diff()
        f_prime = a_prime - b_prime
        return (a_val - b_val, f_prime)
    def __str__(self):
        return f"({str(self.a)} - {str(self.b)})"   
    
class Mult_Op(Bi_Op):
    def diff(self):
        a_val, a_prime = self.a.diff()
        b_val, b_prime = self.b.diff()
        f_prime = (a_val * b_prime) + (a_prime * b_val)
        return (a_val * b_val, f_prime)
    def __str__(self):
        return f"({str(self.a)} * {str(self.b)})"  
    
class Div_Op(Bi_Op):
    def diff(self):
        a_val, a_prime = self.a.diff()
        b_val, b_prime = self.b.diff()
        f_prime = ((a_prime * b_val) - (a_val * b_prime)) / (b_val * b_val)
        return (a_val / b_val, f_prime)
    def __str__(self):
        return f"({str(self.a)} / {str(self.b)})"