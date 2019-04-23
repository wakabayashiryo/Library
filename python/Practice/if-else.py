year = int(input("西暦何年？"))

is_leap = False #Bool type 

if year % 400 == 0:
    is_leap = True
elif year % 100 == 0:
    is_leap = False
elif year % 4 == 0: #ｃ言語でいう"else if""
    is_leap = True
else :
    is_leap = False

if is_leap:
    print("うるう年です")
elif is_leap == False:
    print("平年です")
else :
    pass    #do nothing process
