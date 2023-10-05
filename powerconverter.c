#include "ghcommon.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_power(double volts_p, double decibels, double ohms)
{
    double w;

    if (ohms == 0.0)
        return 0.0;

    volts_p = volts_p * (pow(10, (-decibels / 20)));
    w = pow(volts_p / 1.41421356, 2) / ohms;

    return w;
}

int main(void)
{
    double att;
    double volts;
    double watts;
    double ohms;
    int choice;
    int flag;

    while (TRUE)
    {
        flag = FALSE;

        choice = get_int("\n\n\n[1] Voltage Peak\n[2] Voltage Peak to Peak\n\n[0] Quit\n");

        switch (choice)
        {
        case 0:
            return SUCCESS;
        case 1:
            volts = fabs(get_double("\nEnter RF Peak Voltage: "));
            flag = TRUE;
            break;
        case 2:
            volts = fabs(get_double("\nEnter RF Peak to Peak Voltage: ") / 2.0);
            flag = TRUE;
            break;
        default:
            break;
        }

        if (flag == FALSE)
            continue;

        att = -fabs(get_double("\nEnter Pad Attenuation in dB or 0.0 if none: "));
        ohms = fabs(get_double("\nEnter Load Ohms: "));

        watts = calculate_power(volts, att, ohms);

        if (watts < 1.0)
            printf("\n\nWattage is: %.1f mW", watts * 1000.0);
        else
            printf("\n\nWattage is: %.2f W", watts);
    }
}