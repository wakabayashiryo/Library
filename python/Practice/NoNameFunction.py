# v = lambda 引数１、引数２、引数３...:式
print('No name Function "lambda"')
def calc_5_3(func):
    return func(5,3)

result = calc_5_3(lambda a,b:a*b)
print(result)

result = calc_5_3(lambda a,b:a+b)
print(result)
print("")

#Process to list
print("How abuot map")
num = [1,2,3,4,5]
x2 = lambda a:a*2
print(list(map(x2,num)))
print("")

print("How about filter")
num2 = [1,2,3,11,12,13,21,22,23]
x1 = lambda x : (x%2)==0
print(list(filter(x1,num2)))
