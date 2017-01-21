/* ============================================= */
/* Motor Code */
/* ============================================= */
const int pwmA = 3;
const int pwmB = 11;
const int dirA = 12;
const int dirB = 13;
const int brakeA = 9;
const int brakeB = 8;

const int STOP = 0;
const int SLOW = 45;
const int MEDIUM = 75;
const int FAST = 90;

/* Sensor variables*/
int sensor = frontSensor();
const int VERY_CLOSE = 0;
const int CLOSE = 1;
const int FAR = 2;
const int NOTHING = 3;



void setMotors(int left, int right) {
	analogWrite(pwmA, left);
	analogWrite(pwmB, right);
}

void setReverse() {
	digitalWrite(dirA, HIGH);
	digitalWrite(dirB, HIGH);
}

void setForward() {
	digitalWrite(dirA, LOW);
	digitalWrite(dirB, LOW);
}

void setturn()
{
	delay(500);

	setMotors(STOP, FAST);



}

void brakesOff() {
	digitalWrite(brakeA, LOW);
	digitalWrite(brakeB, LOW);
}

/* ============================================= */
/* Sensor Code */
/* ============================================= */


int frontSensor() {
	int x = analogRead(2);
	if (x > 400) {
		return VERY_CLOSE;
	}
	else if (x > 250) {
		return CLOSE;
	}
	else if (x > 100) {
		return FAR;
	}
	else {
		return NOTHING;
	}
}

/* ============================================= */
/* Setup Code */
/* ============================================= */

void setup() {
	pinMode(pwmA, OUTPUT);  //Set control pins to be outputs
	pinMode(pwmB, OUTPUT);
	pinMode(dirA, OUTPUT);
	pinMode(dirB, OUTPUT);

	analogWrite(pwmA, STOP);
	analogWrite(pwmB, STOP);

	setForward();
	brakesOff();
	setturn();


	delay(1500);
}

/* ============================================= */
/* Controller Code */
/* ============================================= */

void loop()
{
	int sensor = frontSensor();

	switch (sensor) {
	case VERY_CLOSE:
		setReverse();
		setMotors(MEDIUM, MEDIUM);
		break;
	case CLOSE:
		setForward();
		setMotors(STOP, STOP);
		setturn();
		break;
	case FAR:
		setForward();
		setMotors(FAST, FAST);
		break;
	case NOTHING:
		setForward();
		setMotors(FAST, FAST);
		break;
	}
	delay(100);
}

