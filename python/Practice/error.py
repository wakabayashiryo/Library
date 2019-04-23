while True:
    try:
        weight = float(input("What Weight?(kg)"))
        height = float(input("What height?(cm)"))

        height /= 100
        bmi = weight /(height * height)
        break
    except:
        print("Wrong value!input again")

result = ""
if bmi < 18.5 :result = "ヤセ型"
elif bmi < 25 :result = "標準"
elif bmi <30 :result = "肥満"
else : result = "肥満"

print("BMI:",bmi)
print("判定:",result)