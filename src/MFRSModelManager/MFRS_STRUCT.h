#pragma once

struct MFRS_POSITION
{
    float x = 0.0F;
    float y = 0.0F;
};

struct MFRS_MODEL
{
    MFRS_POSITION position;

    float minDetectionAzimuthDeg = -45.0F;
    float maxDetectionAzimuthDeg = 45.0F;

    float minDetectionElevationDeg = 10.0F;
    float maxDetectionElevationDeg = 80.0F;

    float maxDetectionRangeKm = 230.0F;
};
