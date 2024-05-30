package com.iiitb.imageEffectApplication.effectImplementation;

import com.iiitb.imageEffectApplication.service.LoggingService;
import com.iiitb.imageEffectApplication.baseEffects.DiscreteEffect;
import com.iiitb.imageEffectApplication.exception.IllegalParameterException;
import libraryInterfaces.RotationInterface;
import libraryInterfaces.Pixel;


// RotationEffect class implementing the DiscreteEffect interface
public class RotationEffect implements DiscreteEffect
{
    private int val =0 ;
   private String optionName;
    // Method to apply the rotation effect on the image
    public Pixel[][] apply(Pixel[][] image, String fileName, LoggingService loggingService)
    {
        String effectName = "Rotation";
        String optionValues = String.format("%d degrees", val*90 );
        loggingService.addLog(fileName, effectName, optionValues);  // Adding log entry for the applied Rotation effect
        return RotationInterface.applyRotation(image,val);
    }
   // @Override
   // Method to select the rotation option value
     public void selectOptionValue( String optionName,int value) throws IllegalParameterException
     {// Checking the provided option name and setting the corresponding rotation value
       if(optionName.equals("90"))
        {
            val=value ;
        }
        else if(optionName.equals("180"))
        {
           val= value;
        }
        else if(optionName.equals("270"))
        {
           val= value ;
        }
        else if(optionName.equals("0"))
        {
            val = value ;
        }
        else
        {
            throw new IllegalParameterException(); // Throwing an exception for unknown option names
        }
    }
}