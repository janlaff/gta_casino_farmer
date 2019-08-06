// Button constants
const int A_KEY = 21;
const int UP_KEY = 20;
const int DOWN_KEY = 19;
const int RIGHT_KEY = 18;

// Time constants
const int KEY_CLICK_DURATION = 200; // 200ms
const int RACE_DURATION = 15000; // 15s
const int CHEAT_DELAY = 200; // 200ms
const int RESTART_DELAY = 1000; // 1s

// Fwd declaration
class key_holder;

void set_key_state(int key, bool on);
void click_key(int key);
key_holder hold_key(int key);

// Holds button while object is in scope
class key_holder {
public:
  key_holder(int key) : key(key) {
    set_key_state(key, true);
  }

  ~key_holder() {
    set_key_state(key, false);
  }
  
  int key;
};

// Press/Release button
void set_key_state(int key, bool on) {
  if (on) {
    Serial.print("Enabling pin ");
    Serial.println(key);
    analogWrite(key, 255);
  } else {
    Serial.print("Disabling pin ");
    Serial.println(key);
    analogWrite(key, 0);
  }
}

// Simulate key click
void click_key(int key) {
  set_key_state(key, true);
  delay(KEY_CLICK_DURATION);
  set_key_state(key, false);
}

// Hold key for the lifetime of returned object
key_holder hold_key(int key) {
  return key_holder(key);
}

// Initial setup
void setup() {
  pinMode(A_KEY, OUTPUT);
  pinMode(UP_KEY, OUTPUT);
  pinMode(DOWN_KEY, OUTPUT);
  pinMode(RIGHT_KEY, OUTPUT);

  set_key_state(A_KEY, false);
  set_key_state(UP_KEY, false);
  set_key_state(DOWN_KEY, false);
  set_key_state(RIGHT_KEY, false);
}

void loop() {
  // Go to start game with right key
  click_key(RIGHT_KEY);
  
  // Start game
  click_key(A_KEY);
  
  // Goto 6. horse
  for (int i = 0; i < 5; ++i) {
    click_key(DOWN_KEY);
  }
  
  // Select it
  click_key(A_KEY);

  // Goto money increase arrow
  click_key(RIGHT_KEY);
  click_key(UP_KEY);

  {
    // Hold the a key during this scope
    auto a_hold = hold_key(A_KEY);
    delay(CHEAT_DELAY);

    // Start race
    click_key(DOWN_KEY);

    // Wait for result
    delay(RACE_DURATION);
  }

  // Get price if present
  click_key(A_KEY);
  delay(RESTART_DELAY);
}
