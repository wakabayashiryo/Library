

def convert_jou(jou,unit="江戸間"):
    if unit == "江戸間":
        base = 0.88 * 1.76
    elif unit == "京間":
        base = 0.955 * 1.91
    elif unit == "中京間":
        base = 0.91 * 1.82    
    m2 = jou * base
    s = "{0}で{1}畳は{2}m^2".format(unit,jou,m2)
    print(s)
    
print("defoult value of argumant")
convert_jou(6,"江戸間")
convert_jou(6,"京間")
convert_jou(6)
print("")

print("argument with name")
def calcTime(dist,speed):
    t = dist / speed
    t = round(t,1)
    return t

print(calcTime(500,100))
print(calcTime(dist=500,speed=100))
print("")

print("variable length arguments")
def sumArg(*args):
    v = 0
    for n in args: 
        v += n
    return v

print(sumArg(1,2,3))
print(sumArg(1,2,3,4,5))
print(sumArg(1,2,3,4,5,6,7,8,9,10))
