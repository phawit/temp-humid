void setup() {
  int *p;       // declare a pointer to an int data type
  int i = 5, result = 0;
  p = &i;       // now 'p' contains the address of 'i'
  result = *p;  // 'result' gets the value at the address pointed by 'p'
              // i.e., it gets the value of 'i' which is 5
}

void loop() {
 

}
