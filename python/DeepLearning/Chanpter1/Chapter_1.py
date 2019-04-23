def hello():
    
    for i in [1,2,3,4]:
        if i % 2 == 0:
            print("Hello")

class test:
    def __init__(self, name):
        self.name = name
        print("Initialized")

    def hello(self):
        print("Hello"+self.name+"!")

    def goodbye(self):
        print("GoodBye"+self.name+"!")

hello()

m = test("Ryo")#initialize and Hand over objects to m(availal)
m.hello()
m.goodbye()
