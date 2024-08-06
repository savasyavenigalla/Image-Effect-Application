package com.iiitb.imageEffectApplication.effectImplementation;

import com.iiitb.imageEffectApplication.baseEffects.SingleValueParameterizableEffect;
import com.iiitb.imageEffectApplication.exception.IllegalParameterException;
import com.iiitb.imageEffectApplication.service.LoggingService;
import libraryInterfaces.Pixel;
import libraryInterfaces.SharpenInterface;

// SharpenEffect class implementing the SingleValueParameterizableEffect interface
public class SharpenEffect implements SingleValueParameterizableEffect {
    private float amount = 0.0f;
    // Method to apply the sharpen effect on the image
    public Pixel[][] apply(Pixel[][] image, String fileName, LoggingService loggingService){
        String effectName = "Sharpen";
        String optionValues = String.format("%.2f", amount);
        loggingService.addLog(fileName, effectName, optionValues); // Adding log entry for the applied Sharpen effect
        //System.out.println(fileName + " " + optionValues);
        return SharpenInterface.applySharpen(image, amount);
    }

    // Method to set the sharpen parameter value
    public void setParameterValue(float parameterValue) throws IllegalParameterException{
        // Checking if the provided amount is within the valid range
        if (parameterValue <= 100 && parameterValue >= 0)
            amount = parameterValue;
        else{
            throw new IllegalParameterException(); // Throwing an exception for illegal parameter values
        }
    }
}