//package com.iiitb.imageEffectApplication.effectImplementation;
//
//
//import com.iiitb.imageEffectApplication.baseEffects.DiscreteEffect;
//import com.iiitb.imageEffectApplication.baseEffects.PhotoEffect;
//import com.iiitb.imageEffectApplication.exception.IllegalParameterException;
//import com.iiitb.imageEffectApplication.libraryInterfaces.InvertInterface;
//import com.iiitb.imageEffectApplication.service.LoggingService;
//import com.iiitb.imageEffectApplication.libraryInterfaces.Pixel;
//import libraryInterfaces.FlipInterface;
//
//public class Invertimp implements PhotoEffect
//{
//    public Pixel[][] apply(Pixel [][] image, String fileName, LoggingService lservice)
//    {
//        return InvertInterface.applyInvert(image);
//    }
//
//}
//}

package com.iiitb.imageEffectApplication.effectImplementation;
import com.iiitb.imageEffectApplication.baseEffects.PhotoEffect;
import com.iiitb.imageEffectApplication.service.LoggingService;
import libraryInterfaces.InvertInterface;
import libraryInterfaces.SepiaInterface;
import libraryInterfaces.Pixel;

// Class declaration for the Invertimp class implementing the PhotoEffect interface
public class Invertimp implements PhotoEffect{
    // Method to apply the invert effect on the image
    public Pixel[][] apply(Pixel[][] image, String filename, LoggingService loggingService){
        String effectName = "Invert";
        String optionValues = "";
        loggingService.addLog(filename, effectName, optionValues); // Adding log entry for the applied Invert effect
        return InvertInterface.applyInvert(image);
    }
}
