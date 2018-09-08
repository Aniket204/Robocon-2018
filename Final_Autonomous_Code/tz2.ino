void tz2()
{
  while (tz2_enable == true)
  {
    readsensor1();
    readsensor2();
    countercount();
    if (posval1 > 70 && posval2 > 70)
    {
      wait();
    }
    else
    {
      if (counter == 2)
      {
        if (posval2 > 60)
        {
          tz2_start = true ;
        }
        if (tz2_start == true)
        {
          set_speed_medium();
          move_left();
          tz2_start = false ;
        }
        else if (tz2_start == false)
        {
          set_speed_medium();
          move_back();
        }
      }
      if (counter == 3)
      {
        if (tz2_trigger_slippage == true)
        {
          wait();
          delay(200);
          tz2_trigger_slippage = false;
        }

        if (digitalRead(junction3) == HIGH)
        {
          tz2_counter3 = true ;
        }
        if (tz2_counter3 == false)
        {
          set_speed_slow();
          move_right();
        }
        else
        {
          set_speed_fast();
          move_right();
        }
      }
      if ( counter == 4)
      {
        set_speed_medium();
        move_right();
        tz2_trigger_slippage = true ;
      }
      if (counter == 5)
      {
        if (tz2_trigger_slippage == true)
        {
          wait();
          delay(200);
          tz2_trigger_slippage = false;
        }
        set_speed_slow();
        move_front();
      }
      if (counter == 6)
      {
        if (tz2_counter6 == true)
        {
          while (digitalRead(proxy1) != HIGH || digitalRead(proxy2) != HIGH)
          {
            set_speed_medium();
            move_front();
          }
          wait();
          digitalWrite( flasher , LOW);
          delay(1000);
          digitalWrite( flasher , HIGH);
          delay(1000);
          digitalWrite(throw_tz2 , LOW);
          delay(1000);
          digitalWrite(throw_tz2 , HIGH);
          tz2_counter6 = false ;
        }
        set_speed_medium();
        move_back();
        tz2_trigger_slippage = true;
      }
      if (counter == 7)
      {  
         while (posval1 > 70)
        {
          move_back();
          readsensor1();
          if (posval1 < 70)
          {
            break;
          }
        }
        if (tz1_trigger_slipage == true)
        {
          wait();
          delay(200);
          tz1_trigger_slipage = false;
        }
        set_speed_medium();
        move_left();
      }
      if (counter == 8)
      {
        set_speed_fast();
        move_left();
      }
      
        if (counter == 9)
        {
        if (posval2 > 60)
        {
          tz2_counter9 = true;
        }
        if (tz2_counter9 == true)
        {
          if (digitalRead(junction3) == HIGH)
          {
            tz2_counter8 = true ;
          }
          if (tz2_counter8 == false)
          {
            set_speed_tz2();
            move_left();
          }
          else
          {
            set_speed_tz2();
            move_left();
          }
          tz2_counter9 = false;
        }
        else
        {
          set_speed_tz2();
          move_front();
        }
        }
      if (counter == 10)
      {
        set_speed_medium();
        if (posval1 > 60)
        {
          tz2_counter10 = true ;
          //change this if not workin
          if (tz2_counter10 == true)
          {
            set_speed_medium();
            move_front();
          }
          tz2_counter10 = false ;
        }
        else
        {
          wait();
          tz2_enable = false;
          drift_enable = true;
          tz2_counter6 = true ;
          tz2_counter3 = false;
          tz2_counter8 = false;
          tz2_trigger_slippage = true;
          counter = 2;
        }
      }
    }
  }
}
