# adis16488

## Contents:

1. Arduino source code (SPI communication with adis16488 and UART communication with PC)
2. Calculated acceleration, angular velocity and orientation (using complementary filter) and publishing on topic
3. Services for settings registers on Adis16488 (calibration, bias, sample rate, filters, range)
4. Diagnostic - periodical reading status from Adis16488
5. URDF model and TF broadcaster for visualization and debug
6. Yaml file for configuration initial parameters

## Running example:
    roslaunch adis16488 display.launch
or
    roslaunch adis16488 adis_driver.launch
