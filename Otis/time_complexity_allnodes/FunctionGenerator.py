import AD_Forward_Backward_Otis as AD
import numpy as np
import random

Bi_Op_types = [AD.Add_Op_fb, AD.Sub_Op_fb, AD.Mult_Op_fb]
Un_Op_types = [AD.Sin_Op_fb]

def generate_random_function_b(complexity, vars):
    if complexity==1:
        return vars[0]

    leafnodes = []

    def generate_subtree_with_complexity(c, l):
        if (c+1)/2 < l:
            print("too complex for leaf count. Must have l <=(c + 1)/2")
        if c==1:
            leaf = AD.expression_fb()
            leafnodes.append(leaf)
            return [leaf]
            
        unary_next = (np.random.uniform(0,1) < 0.5)
        if  c==2 or (unary_next and c/2 > l):
            subtree = generate_subtree_with_complexity(c - 1, l)
            new_node = AD.Un_Op_fb(subtree[0])
            return [new_node] + subtree
        else:
            c_a = 1
            c_b = c - c_a - 1
            l_a = 1
            l_b = l - 1
            if(c > 3):
                c_a = np.random.randint(1, c/2)
                c_b = c - c_a - 1
                while(c_a + c_b + 1 != c or
                      l_a + l_b != l or
                      l_a > (c_a + 1)/2 or 
                      l_b > (c_b + 1)/2):
                    
                    c_a = np.random.randint(1, c/2)
                    c_b = c - 1 - c_a
                    l_a = np.random.randint(l - (c_b + 1)/2, (c_a + 1)/2 + 1)
                    l_b = l - l_a

            subtree_a = generate_subtree_with_complexity(c_a, l_a)
            subtree_b = generate_subtree_with_complexity(c_b, l_b)
            new_node = AD.Bi_Op_fb(subtree_a[0], subtree_b[0])
            return [new_node] + subtree_a + subtree_b
    
    def randomize_non_leaf_node_types(node):
        if type(node) == AD.expression_fb:
            non_leaves = []
            return node, non_leaves
        if type(node) == AD.Un_Op_fb:
            new_type = Un_Op_types[np.random.randint(len(Un_Op_types))]
            new_subtree_a, non_leaves_a = randomize_non_leaf_node_types(node.a)
            new_root = new_type(new_subtree_a)
            return new_root, [new_root] + non_leaves_a
        if type(node) == AD.Bi_Op_fb:
            new_type = Bi_Op_types[np.random.randint(len(Bi_Op_types))]
            new_subtree_a, non_leaves_a = randomize_non_leaf_node_types(node.a)
            new_subtree_b, non_leaves_b = randomize_non_leaf_node_types(node.b)
            new_root = new_type(new_subtree_a, new_subtree_b)
            return new_root, [new_root] + non_leaves_a + non_leaves_b

    # generate tree with generic operation and expression types
    tree_blank = generate_subtree_with_complexity(complexity, len(vars))

    # fill in types of nodes to be actual operations, variables,  or constants
    if len(tree_blank) > 1:
        tree_filled, non_leaves = randomize_non_leaf_node_types(tree_blank[0])

        leaf_nodes_to_replace = random.sample(leafnodes, k=len(vars))
        for non_leaf in non_leaves:
            if type(non_leaf.a) == AD.expression_fb:
                if non_leaf.a in leaf_nodes_to_replace:
                    non_leaf.a = vars[leaf_nodes_to_replace.index(non_leaf.a)]
                else:
                    non_leaf.a = AD.Const_Exp_fb(np.random.uniform(-2,2))
            if issubclass(type(non_leaf), AD.Bi_Op_fb):
                if type(non_leaf.b) == AD.expression_fb:
                    if non_leaf.b in leaf_nodes_to_replace:
                        non_leaf.b = vars[leaf_nodes_to_replace.index(non_leaf.b)]
                    else:
                        non_leaf.b = AD.Const_Exp_fb(np.random.uniform(-2,2))

    return tree_filled

#n = 5
#
#vars = []
#for i in range(n):
#    vars.append(AD.Var_fb(f"x_{i}", 0))
#
#f = generate_random_function_b(30, vars)
#
#print(f)

