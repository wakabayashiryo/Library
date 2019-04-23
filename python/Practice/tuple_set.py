#what about touple 
#使い方はlistと同じであるが値を操作することができない
#変更したい場合はlist(touple) or touple(list)関数を使用して変更する 
a = (10,20,30)
print(a[1])
print(a[:2])

#what about set
box1 = {'orange','hanmer','blue'}
box2 = {'hanmer','blue'}
print(box1-box2)
print('orange'in box1)
