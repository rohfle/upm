/*
 * Author: Jon Trulson <jtrulson@ics.com>
 * Copyright (c) 2014 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <unistd.h>
#include <iostream>
#include <signal.h>
#include "ehr.hpp"

using namespace std;

int shouldRun = true;

void sig_handler(int signo)
{
  if (signo == SIGINT)
    shouldRun = false;
}


int main()
{
  signal(SIGINT, sig_handler);

//! [Interesting]
  // Instantiate a  Ear-clip Heart Rate sensor on digital pin D2
  upm::EHR* heart = new upm::EHR(2);
  
  // set the beat counter to 0, init the clock and start counting beats
  heart->clearBeatCounter();
  heart->initClock();
  heart->startBeatCounter();

  while (shouldRun)
    {
      // we grab these just for display purposes in this example
      uint32_t millis = heart->getMillis();
      uint32_t beats = heart->beatCounter();

      // heartRate() requires that at least 5 seconds pass before
      // returning anything other than 0
      int hr = heart->heartRate();

      // output milliseconds passed, beat count, and computed heart rate
      cout << "Millis: " << millis << " Beats: " << beats;
      cout << " Heart Rate: " << hr << endl;

      sleep(1);
    }

  heart->stopBeatCounter();
//! [Interesting]

  cout << "Exiting..." << endl;

  delete heart;
  return 0;
}