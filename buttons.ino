const int INPUTBTN = 12;
unsigned long debounceDelay = 50;
unsigned long doubleClickDelay = 500;

void setup() {
  Serial.begin(9600);
}

void loop() { 
 if (waitDoubleClick(INPUTBTN)){
    Serial.println("double click ...");
 }

  if (waitHold(INPUTBTN)){
    Serial.println("hold ...");
  }

  if (waitClick(INPUTBTN)){
    Serial.println("click ...");
 }
}

unsigned long lastDebounceTime = 0;
int stateClick = 0;
int readingClick;
int previousClick = 1;
bool clicked = false;
bool waitClick(int input) {
  readingClick = digitalRead(input);
  
  if (readingClick != previousClick) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
 
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (readingClick != stateClick) {
      stateClick = readingClick;
 
      if (stateClick == 1) {
        clicked = !clicked;
      }
    }
  }

  previousClick = readingClick;

  if(clicked && ((millis() - lastDebounceTime) > doubleClickDelay)) {
    clicked = !clicked;
    return true;
  }

  return false;
}

unsigned long lastClickTime = 0;
unsigned long firstClick = 0;
int stateDoubleClick = 0;
int readingDoubleClick;
int previousDoubleClick = 1;
bool doubleClicked = false;
int clickNum = 0;
bool waitDoubleClick(int input) {
  readingDoubleClick = digitalRead(input);
  if (readingDoubleClick != previousDoubleClick) {
    // reset the debouncing timer
    lastClickTime = millis();
  }
 
  if ((millis() - lastClickTime) > debounceDelay) {
    if (readingDoubleClick != stateDoubleClick) {
      stateDoubleClick = readingDoubleClick;
 
      if (stateDoubleClick == 1) {
        doubleClicked = !doubleClicked;
        if(clickNum == 0) {
          firstClick = millis();
        }
        clickNum += 1;
      }
    }
  }

  previousDoubleClick = readingDoubleClick;

  if((millis() - firstClick) > doubleClickDelay && clickNum > 0) {
      clickNum = 0;
  }

  if(clickNum == 2) {
    clickNum = 0;
    doubleClicked = !doubleClicked;
    return true;
  }

  return false;
}

unsigned long holdDelay = 3000;
unsigned long startHoldDelay = 0;
int stateHold = 0;
int readingHold;
int previousHold = 1;
bool hold = false;
bool waitHold(int input) {
  readingHold = digitalRead(input);
  
  if (readingHold != previousHold) {
    // reset the debouncing timer
    startHoldDelay = millis();
  }
 
  if ((millis() - startHoldDelay) >= holdDelay) {
    if (readingHold != stateHold) {
      hold = true;
    }
  }

  previousHold = readingHold;

  if(hold) {
    hold = !hold;
    startHoldDelay = millis();
    return true;
  }

  return false;
}
