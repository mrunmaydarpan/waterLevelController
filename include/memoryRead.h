void ReadMem()
{
    if (EEPROM.read(maxDistance_mem) > 250)
    {
        EEPROM.write(maxDistance_mem, 120);
    }
    if (EEPROM.read(minDistance_mem) > EEPROM.read(maxDistance_mem))
    {
        EEPROM.write(minDistance_mem, 20);
    }

    if (EEPROM.read(manualOff_mem) > 1)
    {
        EEPROM.write(manualOff_mem, 0);
    }
    if (EEPROM.read(MotorStartThreshold_mem) > 70 ||
        EEPROM.read(MotorStartThreshold_mem) < 20)
    {
        EEPROM.write(MotorStartThreshold_mem, 20);
    }
    if (EEPROM.read(LastMotorState_mem) > 1)
    {
        EEPROM.write(LastMotorState_mem, 0);
    }
    MotorStartThreshold = EEPROM.read(MotorStartThreshold_mem);
    ManualOff = EEPROM.read(manualOff_mem);
    MaxDistance = EEPROM.read(maxDistance_mem);
    MotorState = EEPROM.read(motorState_mem);
    MinDistance = EEPROM.read(minDistance_mem);
    LastMotorState = EEPROM.read(LastMotorState_mem);
    dryRun_LastDistance = EEPROM.read(dryRun_LastDistance_mem);
}