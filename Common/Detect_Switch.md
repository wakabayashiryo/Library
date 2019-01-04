# 組み込みマイコン用スイッチ検出アルゴリズム

- ## スイッチを押して離した後に処理を実行する 
    [ＰＩＣを使用した例](https://github.com/wakabayashiryo/PowerCTRL_MutingRelayUnit.X)

    > void Switch_CountHIGH(void)   

    スイッチが押されいる時間をカウントする   
    注；この関数は1msおきに実行すること(割込み関数などを利用して)

    ~~~c
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

    ~~~c
    uint16_t Switch_ReadTime(void)
    {
        uint16_t store_time = sw_time;

        sw_time = 0;
        
        return store_time;
    }
    ~~~   

    ## main関数での処理
    main関数では押されている時間でスイッチの状態を確認する
    ~~~c
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


- ## スイッチを押した直後に処理を実行する
    - ### 制御フロー
        1. SW1が押される
        2. intervalに値が入力される。
        3. 返り値に１が返される
        4. ボタンから指が離されたらintervalを1ms間隔でデクリメントしていく※intervalが０より大きい時は関数は0を返す
        5. intervalが0になったら次の入力を許可する。
    ~~~c
    uint16_t SW1_IntVal;

    int main(void)
    {
        //SW1の入力をチェックする。押された場合100msの入力禁止の時間を設ける。
        if(CheckSW1(100))
        {
            processes;
        }
        return 0;
    }
    ~~~

    ~~~c
    void SysTick_Handler(void)//1msのタイマー割り込み
    {
        //SWが離されてからデクリメントするようにする
        if((SW1_IntVal>0)&&SW1_is_Pulling)
            //これをしないと押されている間、繰り返し検知してしまう。
            SW1_IntVal--;
    }
    ~~~

    ~~~c
    //intervalで入力禁止の時間を指定(ms)
    //返り値 1:SWxが押された
    //       0:SWが押されていないか、前回の入力からまだ入力禁止の状態
    uint32_t CheckSW1(uint32_t interval)
    {
        uint32_t Stat = 0;
        if(SW1_is_Pushing&&(SW1_IntVal==0))
        {
            SW1_IntVal = interval;
            Stat = 1;
        }
        return Stat;
    }
    ~~~