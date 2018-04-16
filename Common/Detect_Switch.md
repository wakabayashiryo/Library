# 組み込みマイコン用スイッチ検出アルゴリズム

[ＰＩＣを使用した例](https://github.com/wakabayashiryo/PowerCTRL_MutingRelayUnit.X)

> void Switch_CountHIGH(void)   

スイッチが押されいる時間をカウントする   
注；この関数は1msおきに実行すること(割込み関数などを利用して)

~~~   
uint16_t sw_time;

void Switch_CountHIGH(void)
{
    static uint16_t count = 0;
    
    if(Pushed Switch)
    {
        count++;
    }
    else
    {
        sw_time = count;//save time 
        count = 0;
    }
}

/*This function exects ever 1ms*/
void interrupt Handler(void)
{
  Switch_CountHIGH();
}
~~~   

> uint16_t Switch_ReadTime(void)   

Switch_CountHIGH()で計測した時間(ms)を取得する。

~~~ 
uint16_t Switch_ReadTime(void)
{
    uint16_t store_time = sw_time;

    sw_time = 0;
    
    return store_time;
}
~~~   

## main関数での処理
main関数では押されている時間でスイッチの状態を確認する
~~~   
void main(void)
{
    Initialize_functions();

    while(1)
    {
        //pass through "if" when switch was pushed at 1000ms(1s)
        if(Switch_ReadTime()>1000)
        {           
          Procceses
        }
    }
}
~~~