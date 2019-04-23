print("Substitute function for varyable")
def mul_func(a,b):return a*b

def div_func(a,b):return a / b

func = mul_func

result = func(2,3)
print(result)

func2 = div_func
result = func2(10,5)
result = func2(10,5)
print(result)

print("")
print("Specify function to argument of function")
def calc_5_3(func):
    return func(5,3)

result = calc_5_3(mul_func)
print(result)

result = calc_5_3(div_func)
print(result)

