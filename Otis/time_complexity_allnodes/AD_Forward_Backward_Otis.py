import numpy as np
#import random, time
#import matplotlib.pyplot as plt
#import sympy as sp
#from tqdm import tqdm
#import seaborn as sns
#import pandas as pd

# Node Classes

Vars = 0

# Base Expression
# the _fb at the end means it supports both forward and backward mode
class expression_fb:
    def __init__(self):
        self.partial = 0
        self.value = 0

    def __str__(self):
        return "e" 

    def eval(self):
        self.partial = 0
        return "CANT EVALUATE BASE EXPRESSION CLASS"

    def derive():
        return "CANT BACKWARD-DERIVE OF BASE EXPRESSION CLASS"
    
    def derive_forward():
        '''
        Returns a tuple (value, partial)
        '''
        return "CANT FORWARD-DERIVE OF BASE EXPRESSION CLASS"
    def derive_symbolic(self, var_name):
        return "CANT DIFFERENTIATE BASE EXPRESSION CLASS"

# Base Expression Types
    
class Un_Op_fb(expression_fb):
    def __init__(self, a):
        expression_fb.__init__(self)
        self.a = a
    def __str__(self):
        return f"f({str(self.a)})"
    def derive(self):
        if type(self.a) != Const_Exp_fb:
            self.a.partial += self.dthis_da * self.partial
            self.a.derive()

class Bi_Op_fb(expression_fb):
    def __init__(self, a, b):
        expression_fb.__init__(self)
        self.a = a
        self.b = b
    def __str__(self):
        return f"({str(self.a)}.{str(self.b)})"
    def derive(self):
        if type(self.a) != Const_Exp_fb:
            self.a.partial += self.dthis_da * self.partial
            self.a.derive()
        if type(self.b) != Const_Exp_fb:
            self.b.partial += self.dthis_db * self.partial
            self.b.derive()

    
# Usable Expression Types

# Constants
class Const_Exp_fb(Un_Op_fb):
    def __str__(self):
        return str(self.a)
    
    def eval(self):
        self.value = self.a
        return self.a
    def derive(self):
        return
    def derive_forward(self):
        return (self.a, 0)
    def derive_symbolic(self, var_name):
        return Const_Exp_fb(0)

# Variables  
class Var_fb(expression_fb):
    def __init__(self, name, value = None):
        '''
        name  : typeof(string)
        value : typeof(float)
        '''
        self.name = name
        self.value = value
        self.partial = 0
        self.forward_partial = 0
    def __str__(self):
        return self.name
    def eval(self):
        return self.value
    def derive(self):
        return
    def derive_forward(self):
        return (self.value, self.forward_partial)
    def derive_symbolic(self, var):
        return Const_Exp_fb(int(self == var)) # derivative of variable wrt itself is 1, and 0 wrt any other variable
    
# Unary Operations
class Neg_Op_fb(Un_Op_fb):
    def __str__(self):
        return f"-({str(self.a)})"
    def eval(self):
        self.value = -self.a.eval()
        return self.value
    def derive(self):
        self.dthis_da = -1
        Un_Op_fb.derive(self)
        return
    def derive_forward(self):
        val_partial_a = self.a.derive_forward()
        return (-val_partial_a[0], -val_partial_a[1])
    def derive_symbolic(self, var):
        da_dx = self.a.derive_symbolic(var)
        if type(da_dx) == Const_Exp_fb and da_dx.a == 0:
            return Const_Exp_fb(0)
        return Neg_Op_fb(da_dx)
    
class Sin_Op_fb(Un_Op_fb):
    def __str__(self):
        return f"sin({str(self.a)})"
    def eval(self):
        self.value = np.sin(self.a.eval())
        return self.value
    def derive(self):
        self.dthis_da = np.cos(self.a.value)
        Un_Op_fb.derive(self)
        return
    def derive_forward(self):
        val_partial_a = self.a.derive_forward()
        return (np.sin(val_partial_a[0]), np.cos(val_partial_a[0]) * val_partial_a[1])
    def derive_symbolic(self, var):
        da_dx = self.a.derive_symbolic(var)
        if type(da_dx) == Const_Exp_fb and da_dx.a == 0:
            return Const_Exp_fb(0)
        
        return Mult_Op_fb(Cos_Op_fb(self.a), da_dx)

class Cos_Op_fb(Un_Op_fb):
    def __str__(self):
        return f"cos({str(self.a)})"
    def eval(self):
        self.value = np.cos(self.a.eval())
        return self.value
    def derive(self):
        self.dthis_da = -np.sin(self.a.value)
        Un_Op_fb.derive(self)
        return
    def derive_forward(self):
        val_partial_a = self.a.derive_forward()
        return (np.sin(val_partial_a[0]), np.cos(val_partial_a[0]) * val_partial_a[1])
    def derive_symbolic(self, var):
        da_dx = self.a.derive_symbolic(var)
        if type(da_dx) == Const_Exp_fb and da_dx.a == 0:
            return Const_Exp_fb(0)
        return Mult_Op_fb(Neg_Op_fb(Sin_Op_fb(self.a)), da_dx)
        
class Exp_Op_fb(Un_Op_fb):
    def __str__(self):
        return f"exp({str(self.a)})"
    def eval(self):
        self.value = np.exp(self.a.eval())
        return self.value
    def derive(self):
        self.dthis_da = np.exp(self.a.value)
        Un_Op_fb.derive(self)
        return
    def derive_forward(self):
        val_partial_a = self.a.derive_forward()
        return (np.exp(val_partial_a[0]), np.exp(val_partial_a[0]) * val_partial_a[1])
    def derive_symbolic(self, var):
        da_dx = self.a.derive_symbolic(var)
        if type(da_dx) == Const_Exp_fb and da_dx.a == 0:
            return Const_Exp_fb(0)        
        return Mult_Op_fb(Exp_Op_fb(self.a), da_dx)

# Binary Operations
class Add_Op_fb(Bi_Op_fb):
    def __str__(self):
        return f"({str(self.a)} + {str(self.b)})"
    def eval(self):
        self.value = self.a.eval() + self.b.eval()
        return self.value
    def derive(self):
        self.dthis_da = 1
        self.dthis_db = 1
        Bi_Op_fb.derive(self)
        return  
    def derive_forward(self):
        val_partial_a = self.a.derive_forward()
        val_partial_b = self.b.derive_forward()
        return (val_partial_a[0] + val_partial_b[0], val_partial_a[1] + val_partial_b[1])    
    def derive_symbolic(self, var):
        da_dx = self.a.derive_symbolic(var)
        db_dx = self.b.derive_symbolic(var)
        if type(da_dx) == Const_Exp_fb and da_dx.a == 0:
            if type(db_dx) == Const_Exp_fb and db_dx.a == 0:
                return Const_Exp_fb(0)       
            return db_dx
        if type(db_dx) == Const_Exp_fb and db_dx.a == 0:
            return da_dx   
        return Add_Op_fb(da_dx, db_dx)
    
class Sub_Op_fb(Bi_Op_fb):
    def __str__(self):
        return f"({str(self.a)} - {str(self.b)})"
    def eval(self):
        self.value = self.a.eval() - self.b.eval()
        return self.value
    def derive(self):
        self.dthis_da = 1
        self.dthis_db = -1
        Bi_Op_fb.derive(self)
        return   
    def derive_forward(self):
        val_partial_a = self.a.derive_forward()
        val_partial_b = self.b.derive_forward()
        return (val_partial_a[0] - val_partial_b[0], val_partial_a[1] - val_partial_b[1])   
    def derive_symbolic(self, var):
        da_dx = self.a.derive_symbolic(var)
        db_dx = self.b.derive_symbolic(var)
        if type(da_dx) == Const_Exp_fb and da_dx.a == 0:
            if type(db_dx) == Const_Exp_fb and db_dx.a == 0:
                return Const_Exp_fb(0)       
            return Neg_Op_fb(db_dx) 
        if type(db_dx) == Const_Exp_fb and db_dx.a == 0:
            return da_dx   
        return Sub_Op_fb(da_dx, db_dx)
    
class Mult_Op_fb(Bi_Op_fb):
    def __str__(self):
        return f"({str(self.a)} * {str(self.b)})"  
    def eval(self):
        self.value = self.a.eval() * self.b.eval()
        return self.value
    def derive(self):
        self.dthis_da = self.b.value
        self.dthis_db = self.a.value
        Bi_Op_fb.derive(self)
        return
    def derive_forward(self):
        val_partial_a = self.a.derive_forward()
        val_partial_b = self.b.derive_forward()
        return (val_partial_a[0] * val_partial_b[0], val_partial_a[1] * val_partial_b[0] + val_partial_b[1] * val_partial_a[0]) 
    def derive_symbolic(self, var):
        da_dx = self.a.derive_symbolic(var)
        db_dx = self.b.derive_symbolic(var)
        if type(da_dx) == Const_Exp_fb and da_dx.a == 0:
            if type(db_dx) == Const_Exp_fb and db_dx.a == 0:
                return Const_Exp_fb(0)       
            return Mult_Op_fb(self.a, db_dx)
        if type(db_dx) == Const_Exp_fb and db_dx.a == 0:
            return Mult_Op_fb(self.b, da_dx)
        return Add_Op_fb(Mult_Op_fb(self.a, db_dx), Mult_Op_fb(self.b, da_dx))
#quick test code

x_1 = Var_fb("x_1", 2.0)
x_2 = Var_fb("x_2", 3.0)

#func = Add_Op_fb(Mult_Op_fb(x_1, x_2), Sin_Op_fb(x_2))
#
##func.eval()
##func.partial = 1
##func.derive()
##print("dx_1 f", x_1.partial)
##print("dx_2 f", x_2.partial)
#
#print(func)
#print(x_1.derive_symbolic(x_1))
#print(func.derive_symbolic(x_1))
        
