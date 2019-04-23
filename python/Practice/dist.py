# variable = {'key1':value1,'key2':value2,'key3':value3,}

#how to set Data of Dist type 
ages = {'suzuki':30,'inoue':20,'itou':22}
#refer to dist type
print("itou = ",ages['itou'])
#set to dist type
ages['itou'] = 30
print(ages)

#arrage keys in dist
print(ages.keys())
print(sorted(ages.keys()))