package com.iiitb.imageEffectApplication.effectImplementation;
import com.iiitb.imageEffectApplication.baseEffects.PhotoEffect;
import com.iiitb.imageEffectApplication.service.LoggingService;
import libraryInterfaces.GrayscaleInterface;
import libraryInterfaces.Pixel;

// GrayscaleEffect class implementing the PhotoEffect interface
public class GrayscaleEffect implements PhotoEffect{
    // Method to apply the grayscale effect on the image
    public Pixel[][] apply(Pixel[][] image, String filename, LoggingService loggingService){
        return GrayscaleInterface.applyGrayscale(image);
    }
}
