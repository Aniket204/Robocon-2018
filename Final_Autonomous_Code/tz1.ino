void tz1()
{
  while (tz1_enable == true)
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
        set_speed_medium();
        move_right();
      }
      if (counter == 3)
      { //original
        set_speed_medium();
        move_right();
      }

      if (counter == 4)
      {
        if (tz1_trigger_slipage == true)
        {
          wait();
          delay(400);
          tz1_trigger_slipage = false;
        }
        set_speed_medium();           //change to slow if needed
        move_front();
      }

      if (counter == 5)
      {
        if (tz1_counter5 == true)
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
          digitalWrite(throw_tz1 , LOW);
          delay(1000);
          digitalWrite(throw_tz1 , HIGH);
          tz1_counter5 = false ;
        }
        set_speed_medium();
        move_back();
        tz1_trigger_slipage = true;
      }

      if (counter == 6)
      {

        while (posval1 > 70)
        {
          move_back();
          readsensor1();
          countercount();
          if (posval1 < 70)
          {
            break;
          }
        }
        if (tz1_trigger_slipage == true)
        {
          wait();
          delay(400);
          tz1_trigger_slipage = false;
        }
        set_speed_medium();
        move_left();
      }
      if (counter == 7)
      {
        while (posval1 > 70)
        {
          move_front();
          readsensor1();
          countercount();
          if (posval1 < 70)
          {
            break;
          }
        }
        set_speed_medium();
        move_left();
      }
      if (counter == 8)
      {
        set_speed_medium();
        while (digitalRead(junction3) == LOW)
        {
          move_left();
          countercount();
          readsensor1();
          readsensor2();
        }
        wait();
        delay(50);
        tz1_enable = false ;
        tz1_counter5 = true;
        tz1_trigger_slipage = true;
        tz1_drift_enable = true;
        counter = 2;
      }
    }
  }
}
