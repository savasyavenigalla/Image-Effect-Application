package com.iiitb.imageEffectApplication.effectImplementation;

import com.iiitb.imageEffectApplication.baseEffects.SingleValueParameterizableEffect;
import com.iiitb.imageEffectApplication.exception.IllegalParameterException;
import com.iiitb.imageEffectApplication.service.LoggingService;
import libraryInterfaces.ContrastInterface;
import libraryInterfaces.Pixel;

// ContrastEffect class implementing the SingleValueParameterizableEffect interface
public class ContrastEffect implements SingleValueParameterizableEffect{
    private float amount;
    // Method to apply the contrast effect on the image
    public Pixel[][] apply(Pixel[][] image, String fileName, LoggingService loggingService){
        return ContrastInterface.applyContrast(image,amount);
    }

    @Override
    // Method to set the contrast parameter value
    public void setParameterValue(float parameterValue) throws IllegalParameterException {
        if(amount<=200 && amount>=0){ // Checking if the provided amount is within the valid range
            amount=parameterValue; // Setting the contrast amount value
        }
        else{
            throw new IllegalParameterException(); // Throwing an exception for illegal parameter values
        }
    }
}
