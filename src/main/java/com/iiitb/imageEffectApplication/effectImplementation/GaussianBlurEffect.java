package com.iiitb.imageEffectApplication.effectImplementation;

import com.iiitb.imageEffectApplication.exception.IllegalParameterException;
import libraryInterfaces.*;
import com.iiitb.imageEffectApplication.service.LoggingService;
import com.iiitb.imageEffectApplication.baseEffects.SingleValueParameterizableEffect;

// GaussianBlurEffect class implementing the SingleValueParameterizableEffect interface
public class GaussianBlurEffect implements SingleValueParameterizableEffect{
    private float amountValue = 0;
    // Method to apply the Gaussian blur effect on the image
    public Pixel[][]apply(Pixel[][] image, String filename, LoggingService loggingService){
        String effectName = "Gaussian Blur";
        String optionValues = String.format("%.2f", amountValue);
        loggingService.addLog(filename, effectName, optionValues); // Adding log entry for the applied Gaussian blur effect
        return GaussianBlurInterface.applyGaussianBlur(image, amountValue);
    }

    // Method to set the Gaussian blur parameter value
    public void setParameterValue(float amount1) throws IllegalParameterException{
        if(amount1 >= -200 && amount1 <= 200){ // Checking if the provided amount is within the valid range
            amountValue = amount1;
        }
        else{
            throw new IllegalParameterException(); // Throwing an exception for illegal parameter values
        }
    }
}