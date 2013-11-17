#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#include "helpers.h"
#include "nmea.h"


START_TEST (test_nmea_gpgga_parse)
{
    gpgga_t *loc = (gpgga_t *)malloc(sizeof(gpgga_t));
    nmea_parse_gpgga("$GPGGA,001038.00,3334.2313457,N,11211.0576940,W,2,04,5.4,354.682,M,-26.574,M,7.0,0138*79", loc);

    char buf[48];

    snprintf(buf, sizeof(buf), "The readed latitude is: %f", loc->latitude);
    ck_assert_double_eq(3334.2313457, loc->latitude, buf);

    snprintf(buf, sizeof(buf), "The readed lat is: %c", loc->lat);
    ck_assert_msg(loc->lat == 'N', buf);

    snprintf(buf, sizeof(buf), "The readed longitude is: %f", loc->longitude);
    ck_assert_double_eq(11211.057694, loc->longitude, buf);

    snprintf(buf, sizeof(buf), "The readed lon is: %c", loc->lon);
    ck_assert_msg(loc->lon == 'W', buf);

    snprintf(buf, sizeof(buf), "The readed quality is: %d", loc->quality);
    ck_assert_msg(loc->quality == 2, buf);

    snprintf(buf, sizeof(buf), "The readed satellites is: %d", loc->satellites);
    ck_assert_msg(loc->satellites == 4, buf);

    snprintf(buf, sizeof(buf), "The readed altitude is: %lf", loc->altitude);
    ck_assert_double_eq(354.682, loc->altitude, buf);
}
END_TEST

START_TEST (test_nmea_gprmc_parse)
{
    gprmc_t *loc = (gprmc_t *)malloc(sizeof(gprmc_t));
    nmea_parse_gprmc("$GPRMC,081836,A,3751.65,S,14507.36,E,000.05,360.0,130998,011.3,E*62", loc);

    char buf[48];

    snprintf(buf, sizeof(buf), "The readed latitude is: %f", loc->latitude);
    ck_assert_double_eq(3751.65, loc->latitude, buf);

    snprintf(buf, sizeof(buf), "The readed lat is: %c", loc->lat);
    ck_assert_msg(loc->lat == 'S', buf);

    snprintf(buf, sizeof(buf), "The readed longitude is: %f", loc->longitude);
    ck_assert_double_eq(14507.36, loc->longitude, buf);

    snprintf(buf, sizeof(buf), "The readed lon is: %c", loc->lon);
    ck_assert_msg(loc->lon == 'E', buf);

    snprintf(buf, sizeof(buf), "The readed speed is: %lf", loc->speed);
    ck_assert_double_eq(0.05, loc->speed, buf);

    snprintf(buf, sizeof(buf), "The readed course/angle is: %lf", loc->course);
    ck_assert_msg(loc->course == 360, buf);
}
END_TEST

Suite *nmea_suite(void)
{
    Suite *s = suite_create("NMEA");
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_nmea_gpgga_parse);
    tcase_add_test(tc_core, test_nmea_gprmc_parse);
    suite_add_tcase(s, tc_core);

    return s;
}

