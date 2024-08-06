package com.iiitb.imageEffectApplication.effectImplementation;
import com.iiitb.imageEffectApplication.baseEffects.PhotoEffect;
import com.iiitb.imageEffectApplication.service.LoggingService;
import libraryInterfaces.SepiaInterface;
import libraryInterfaces.Pixel;

// Class declaration for the SepiaEffect class implementing the PhotoEffect interface
public class SepiaEffect implements PhotoEffect{
    // Method to apply the sepia effect on the image
    public Pixel[][] apply(Pixel[][] image, String filename, LoggingService loggingService){
        String effectName = "Sepia";
        String optionValues = "";
        loggingService.addLog(filename, effectName, optionValues); // Adding log entry for the applied Sepia effect
        return SepiaInterface.applySepia(image);
    }
}

