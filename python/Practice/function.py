#動物の最高速度を辞書型で定義
animal_speed_dict = {
    "チーター":110,"トナカイ":80,
    "シマウマ":60,"ライオン":58,
    "キ リ ン":50,"ラ ク ダ":30,
}
#東京から各都市までの距離を辞書型で定義
distance_dict = {
    "静  岡":183.7,
    "名古屋":350.6,
    "大  阪":507.5,
}

#時間を計算する関数を定義
def calc_time(dist,speed):
    t = dist /speed
    t = round(t,1)
    return t

#動物の各都市までの時間を計測する関数を定義
def calc_animal(animal,speed):
    res = "|"+animal
    for city in sorted(distance_dict.keys()):
        dist = distance_dict[city]
        t = calc_time(dist,speed)
        res += "|{0:>6}".format(t)
    return res + "|"
print("+--------+------+------+------+")
print("|動物名前",end="")
for city in sorted(distance_dict.keys()):
    print("|"+city,end="")
print("|")
print("+--------+------+------+------+")

for animal,speed in animal_speed_dict.items():
    s = calc_animal(animal,speed)
    print(s)
print("+--------+------+------+------+")
