import numpy as np
import random, time
import matplotlib.pyplot as plt
from tqdm import tqdm

x_Var = None
Vars = 0
# Node Classes

START = time.time()


# Base Expression
class expression:
    def eval(self):
        raise NotImplementedError("This method should be overridden.")
    
    def __str__():
        return "EXPRESSION"

    def diff():
        return "(expression value, expression derivative)"

# Base Expression Types
    
class Un_Op (expression):
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
class Const_Exp(Un_Op):
    def __str__(self):
        return str(self.a)
    
    def diff(self):
        return (self.a, 0)

    def eval(self):
        return self.a

# Variables  
class X_Exp(expression):
    def __init__(self):
        return
    def __str__(self):
        return "x"

    def diff(self):
        return (x_Var, 1)

    def eval(self):
        return x_Var
    
# Unary Operations
class Sin_Op(Un_Op):
    def __str__(self):
        return f"sin({str(self.a)})"
    def diff(self):
        a_val, a_prime = self.a.diff()
        f_prime = np.cos(a_val) * a_prime
        return (np.sin(a_val), f_prime)

    def eval(self):
        return np.sin(self.a.eval())
    
class Cos_Op(Un_Op):
    def diff(self):
        a_val, a_prime = self.a.diff()
        f_prime = -np.sin(a_val) * a_prime
        return (np.cos(a_val), f_prime)
    def __str__(self):
        return f"cos({str(self.a)})"

    def eval(self):
        return np.cos(self.a.eval())
    
class Log_Op(Un_Op):
    def diff(self):
        a_val, a_prime = self.a.diff()
        if a_val <= 0:
            return (None, None)
        f_prime = (1/a_val) * a_prime
        return (np.log(a_val), f_prime)   
    def __str__(self):
        return f"ln({str(self.a)})"

    def eval(self):
        val = self.a.eval()
        return np.log(val) if val > 0 else None
    
class Exp_Op(Un_Op):
    def diff(self):
        a_val, a_prime = self.a.diff()
        f_prime = np.exp(a_val) * a_prime
        return (np.exp(a_val), f_prime)
    def __str__(self):
        return f"exp({str(self.a)})"

    def eval(self):
        return np.exp(self.a.eval())

# Binary Operations
class Add_Op(Bi_Op):
    def diff(self):
        a_val, a_prime = self.a.diff()
        b_val, b_prime = self.b.diff()
        return (a_val + b_val,  a_prime + b_prime)
    def __str__(self):
        return f"({str(self.a)} + {str(self.b)})"

    def eval(self):
        return self.a.eval() + self.b.eval()

class Sub_Op(Bi_Op):
    def diff(self):
        a_val, a_prime = self.a.diff()
        b_val, b_prime = self.b.diff()
        f_prime = a_prime - b_prime
        return (a_val - b_val, f_prime)
    def __str__(self):
        return f"({str(self.a)} - {str(self.b)})"

    def eval(self):
        return self.a.eval() - self.b.eval()
    
class Mult_Op(Bi_Op):
    def diff(self):
        a_val, a_prime = self.a.diff()
        b_val, b_prime = self.b.diff()
        f_prime = (a_val * b_prime) + (a_prime * b_val)
        return (a_val * b_val, f_prime)
    def __str__(self):
        return f"({str(self.a)} * {str(self.b)})"

    def eval(self):
        return self.a.eval() * self.b.eval()
    
class Div_Op(Bi_Op):
    def diff(self):
        a_val, a_prime = self.a.diff()
        b_val, b_prime = self.b.diff()
        if b_val == 0:
            return (None, None)
        f_prime = ((a_prime * b_val) - (a_val * b_prime)) / (b_val * b_val)
        return (a_val / b_val, f_prime)
    def __str__(self):
        return f"({str(self.a)} / {str(self.b)})"

    def eval(self):
        denom = self.b.eval()
        return self.a.eval() / denom if denom != 0 else None


def generate_complex_function(complexity, positive = False, nonzero = False):
    # Add positive check and nonzero check
    global Vars
    if complexity == 1:
        if Vars == 0:
            Vars += 1
            return X_Exp()
        else:
            if random.randint(1,2) == 1:
                Vars += 1
                return X_Exp()
            else:
                return Const_Exp(random.randint(2, 10))
    else:
        operation = random.choice(['add', 'sub', 'mul'])
        if operation in ['sin', 'cos', 'exp', 'log']:
            if operation == 'log':
                return Log_Op(generate_complex_function(complexity - 1, positive = True))
            return {
                'sin': Sin_Op,
                'cos': Cos_Op,
                'exp': Exp_Op,
            }[operation](generate_complex_function(complexity - 1))
        else:
            left = random.randint(1, complexity - 1)
            right = complexity - left

            left_exp = generate_complex_function(left)
            right_exp = generate_complex_function(right)

            if operation == 'div':
                return Div_Op(generate_complex_function(left), generate_complex_function(right, nonzero = True))
            
            return {
                'add': Add_Op,
                'sub': Sub_Op,
                'mul': Mult_Op,
            }[operation](generate_complex_function(left), generate_complex_function(right))

def measure_diff_time(complexity, x_val, repeats=10000, h=1e-5):
    global first, x_Var
    times_AD_sample = []
    times_FD_sample = []
    times_eval = []
    for i in tqdm(range(repeats), leave = False):
        x_Var = x_val
        first = True
        func = generate_complex_function(complexity)
        
        start_time = time.time()
        func.diff()
        end_time = time.time()
        times_AD_sample.append(end_time - start_time)
        
        start_time = time.time()
        f_x = func.eval()
        if f_x is not None:
            x_Var = x_val + h
            f_x_h = func.eval()
            if f_x_h is not None:
                derivative = (f_x_h - f_x) / h 
        end_time = time.time()
        times_FD_sample.append(end_time - start_time)
        
        start_time = time.time()
        f_x = func.eval()
        end_time = time.time()
        times_eval.append(end_time - start_time)

    average_time_AD = sum(times_AD_sample) / len(times_AD_sample)
    average_time_FD = sum(times_FD_sample) / len(times_FD_sample)
    average_time_eval = sum(times_eval) / len(times_eval)
    times_AD.append(average_time_AD) 
    times_FD.append(average_time_FD)
    times_Eval.append(average_time_eval)


times_AD = []
times_FD = []
times_Eval = []
complexity = [i for i in range(10)]
for i in tqdm(complexity):
    measure_diff_time(i+1, 2)

plt.plot(complexity, times_AD, label='Automatic Differentiation', color='blue') 
plt.plot(complexity, times_FD, label='Finite Differences', color='green')
plt.plot(complexity, times_Eval, label='Function Evaluation', color='red')

plt.xlabel('Complexity Level')
plt.ylabel('Computation Time (seconds)')
plt.title('Comparison of Differentiation Methods by Complexity')

plt.legend()

plt.grid(True)
print(time.time() - START)

plt.show()

