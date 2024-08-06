package com.iiitb.imageEffectApplication.effectImplementation;



import com.iiitb.imageEffectApplication.baseEffects.ParameterizableEffect;
import com.iiitb.imageEffectApplication.exception.IllegalParameterException;
import com.iiitb.imageEffectApplication.service.LoggingService;
import libraryInterfaces.HueSaturationInterface;
import libraryInterfaces.Pixel;

// HueSaturationEffect class implementing the ParameterizableEffect interface
public class HueSaturationEffect implements ParameterizableEffect {
    private float hueValue = 0.0f;
    private float saturationValue = 0.0f;
    // Method to apply the Hue-Saturation effect on the image
    public Pixel[][] apply(Pixel[][] image, String fileName, LoggingService loggingService){
        // Applying the HueSaturation effect
        Pixel[][] modifiedImage = HueSaturationInterface.applyHueSaturation(image, saturationValue, hueValue);
        String effectName = "Hue-Saturation";
        String optionValues = String.format("Hue: %.2f, Saturation: %.2f", hueValue, saturationValue);
        loggingService.addLog(fileName, effectName, optionValues); // Adding log entry for the applied Hue-Saturation effect
        return modifiedImage;
    }

    // Method to set the parameter values for Hue and Saturation
    public void setParameter(String paramName, float value) throws IllegalParameterException{
        // Checking the provided parameter name and setting the corresponding value
        if(paramName.equals("Hue")){
            hueValue = value;
        }
        else if(paramName.equals("Saturation")){
            saturationValue = value;
        }
        else if(value > 100 || value < 0){
            throw new IllegalParameterException(); // Throwing an exception for illegal parameter values
        }
        else{
            throw new IllegalParameterException(); // Throwing an exception for unknown parameter names
        }
    }
}
