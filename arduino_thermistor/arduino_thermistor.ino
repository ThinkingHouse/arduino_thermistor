// к какому аналоговому контакту мы подключены
#define THERMISTOR_PIN A0

// сколько показаний берется для определения среднего значения
#define NUM_SAMPLES 5

// емкость второго резистора в цепи
#define RESISTOR_1 2500.0f

// Steinhart–Hart coefficients
#define STEINHART_HART_A 0.001257781910979988f
#define STEINHART_HART_B 0.00026769677645820556f
#define STEINHART_HART_C 0.00000014029480878874336f

double getTemerature()
{
    double result = 0;
    
    double resistor_2 = 0;
    
    for (uint8_t i = 0; i < NUM_SAMPLES; i++) 
    {
        resistor_2 += analogRead(THERMISTOR_PIN);
        delay(10);
    }

    resistor_2 /= NUM_SAMPLES;

    Serial.print("temp analog reading "); Serial.println(resistor_2);

    // конвертируем значение в сопротивление

    resistor_2 = (resistor_2 / 1023.0f) * 3.3f;
    resistor_2 =(RESISTOR_1 * resistor_2)/(3.3f - resistor_2);

    Serial.print("Thermistor resistance ");
    Serial.println(resistor_2);

    result = (1.0f / (STEINHART_HART_A + STEINHART_HART_B * log(resistor_2) + STEINHART_HART_C * (log(resistor_2) * log(resistor_2) * log(resistor_2)))) - 273.15f;

    return result;
}

void setup(void) 
{
    Serial.begin(115200);
    analogReference(EXTERNAL);
}

void loop(void) 
{
    // Получаем температуру
    double temperature = getTemerature();
    Serial.print("Temp ");Serial.println(temperature, 2);
    delay(1000);
}
