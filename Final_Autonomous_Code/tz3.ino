void tz3()
{
  while (tz3_enable == true)
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
          tz3_start = true ;
        }
        if (tz3_start == true)
        {
          set_speed_medium();
          move_left();
          tz3_start = false ;
        }
        else if (tz3_start == false)
        {
          set_speed_medium();
          move_back();
        }
      }
      if (counter == 3)
      {
        if (tz3_trigger_slippage == true)
        {
          wait();
          delay(200);
          tz3_trigger_slippage = false;
        }

        if (digitalRead(junction3) == HIGH)
        {
          tz3_counter3 = true ;
        }
        if (tz3_counter3 == false)
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
      if ( counter == 4 || counter == 5 || counter == 6 )
      {
        set_speed_fast();
        move_right();
      }
      if (counter == 7)
      {
        set_speed_medium();
        move_right();
        tz3_trigger_slippage = true;
      }
      if (counter == 8)
      {
        if (tz3_trigger_slippage == true)
        {
          wait();
          delay(200);
          tz3_trigger_slippage = false;
        }
        set_speed_slow();
        move_front();
      }
      if (counter == 9)
      {
        if (tz3_counter9 == true)
        {
          while (digitalRead(proxy1) != HIGH || digitalRead(proxy2) != HIGH)
          {
            set_speed_medium();
            move_front();
          }
          digitalWrite( flasher , LOW);
          delay(1000);
          digitalWrite( flasher , HIGH);
          delay(1000);
          digitalWrite(throw_tz3 , LOW);
          delay(1000);
          digitalWrite(throw_tz3 , HIGH);
          tz3_counter9 = false;
        }
        set_speed_medium();
        move_back();
        tz3_trigger_slippage = true;
      }
      if (counter == 10)
      {
        if (tz3_trigger_slippage == true)
        {
          wait();
          delay(200);
          tz3_trigger_slippage = false;
        }
        set_speed_slow();
        move_left();
      }
      if (counter == 11 || counter == 12 || counter == 13 || counter == 14)
      {
        set_speed_fast();
        move_left();
      }
      if (counter == 15)
      {
        /* if (posval2 > 60)
          {
           set_speed_medium();
           move_left();
          }
          else
          {
           set_speed_slow();
           move_front();
          }*/

        if (posval2 > 60)
        {
          tz3_counter15 = true;
        }
        if (tz3_counter15 == true)
        {
          if (digitalRead(junction3) == HIGH)
          {
            tz3_counter15_j3 = true ;
          }
          if (tz3_counter15_j3 == false)
          {
            set_speed_fast();
            move_left();
          }
          else
          {
            set_speed_slow();
            move_left();
          }
          tz3_counter15 = false;
        }
        else
        {
          set_speed_slow();
          move_front();
        }
      }
      if (counter == 16)
      {
        if (posval1 > 60)
        {
          tz3_counter16 = true ;
          if (tz3_counter16 == true)
          {
            set_speed_medium();
            move_front();
          }
          tz3_counter16 = false ;
        }
        else
        {
          wait();
          tz3_enable = false;
          drift_enable = true;
          tz3_counter9 = true;
          tz3_counter15_j3 = false ;
          
          counter = 2;
        }
      }
    }
  }
}
