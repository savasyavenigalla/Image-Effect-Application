package com.iiitb.imageEffectApplication.effectImplementation;

import com.iiitb.imageEffectApplication.exception.IllegalParameterException;
import libraryInterfaces.*;
import com.iiitb.imageEffectApplication.service.LoggingService;
import com.iiitb.imageEffectApplication.baseEffects.SingleValueParameterizableEffect;

// BrightnessEffect class implementing the SingleValueParameterizableEffect interface
public class BrightnessEffect implements SingleValueParameterizableEffect{
    private float amountValue = 0;
    // Method to apply the brightness effect on the image
    public Pixel[][]apply(Pixel[][] image, String filename, LoggingService loggingService){

        String effectName = "Brightness";
        String optionValues = String.format("%.2f", amountValue); // Formatting the option values for logging
        loggingService.addLog(filename, effectName, optionValues); // Adding log entry for the applied brightness effect
        return BrightnessInterface.applyBrightness(image, amountValue);


    }
    // Method to set the brightness parameter value
    public void setParameterValue(float amount1) throws IllegalParameterException{
        if(amount1 >= -200 && amount1 <= 200){ // Checking if the provided amount is within the valid range
            amountValue = amount1;
        }
        else{ // Throwing an exception for illegal parameter values
            throw new IllegalParameterException();
        }
    }
}


