//// package com.iiitb.imageEffectApplication.service;
//// import java.sql.Timestamp;
//// import java.text.SimpleDateFormat;
//// import java.time.format.DateTimeFormatter;
//// import java.util.Date;
//// import com.iiitb.imageEffectApplication.model.LogModel;
//// import org.springframework.stereotype.Service;
//// import java.time.LocalDateTime;
//// import java.util.ArrayList;
//// import java.util.List;
//
//// @Service
//// public class LoggingService {
////     private ArrayList<LogModel> logs=new ArrayList<LogModel>();
//
////     public void addLog(String fileName, String effectName, String optionValues) {
////         //Timestamp timestamp=new Timestamp(System.currentTimeMillis());
////         //LocalDateTime endTimestamp = LocalDateTime.parse(endTime, DateTimeFormatter.ISO_DATE_TIME);
////         LocalDateTime timestamp=LocalDateTime.now();
////         LogModel log= new LogModel(timestamp.toString(),fileName, effectName, optionValues);
////         logs.add(log);
////         return;
////     }
////     public List<LogModel> getAllLogs() {
////         return logs;
////     }
//
////     public List<LogModel> getLogsByEffect(String effectName) {
////         ArrayList<LogModel>sortedLogs=new ArrayList<LogModel>();
////         for(int i=0;i< logs.size();i++){
////             if(logs.get(i).getEffectName().equals(effectName)){
////                 sortedLogs.add(logs.get(i));
////             }
////         }
////         return sortedLogs;
////     }
//
////     public void clearLogs() {
////         logs.clear();
////         return;
////     }
//
////     public List<LogModel> getLogsBetweenTimestamps(LocalDateTime startTime, LocalDateTime endTime) {
////         System.out.println("start time"+startTime);
////         System.out.println("end time"+endTime);
////         return new ArrayList<LogModel>();
////     }
//// }
//package com.iiitb.imageEffectApplication.service;//package com.iiitb.imageEffectApplication.service;
//import org.springframework.stereotype.Service;
//import com.iiitb.imageEffectApplication.model.LogModel;
//
//import java.io.*;
//import java.text.SimpleDateFormat;
//import java.time.LocalDateTime;
//import java.time.format.DateTimeFormatter;
//import java.time.format.DateTimeParseException;
//import java.util.ArrayList;
//import java.util.Date;
//import java.util.List;
//import java.util.concurrent.ExecutorService;
//import java.util.concurrent.Executors;
//@Service
//public class LoggingService {
//
//    private static final int THREAD_POOL_SIZE = 5; // Number of threads in the pool
//    private ExecutorService threadPool;
//    private static final String LOG_FILE_PATH = "logging.txt";
//    private List<LogModel> logs = new ArrayList<>();
//
//    public LoggingService() {
//        threadPool = Executors.newFixedThreadPool(THREAD_POOL_SIZE);
//        loadLogs();
//    }
//
//    public void addLog(String fileName, String effectName, String optionValues) {
//        threadPool.submit(() -> writeToLogFile(fileName, effectName, optionValues));
//    }
//
//    private void writeToLogFile(String fileName, String effectName, String optionValues) {
//        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
//        String timestamp = dateFormat.format(new Date());
//
//        try (PrintWriter w = new PrintWriter(new BufferedWriter(new FileWriter(LOG_FILE_PATH, true)))) {
//            String logEntry = String.format("%s\t%s\t%s\t%s\n", timestamp, fileName, effectName, optionValues);
//            w.write(logEntry);
//            LogModel log = new LogModel(timestamp, fileName, effectName, optionValues);
//            logs.add(log);
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//    }
//
//    public List<LogModel> getAllLogs() {
//        return logs;
//    }
//
//    public List<LogModel> getLogsByEffect(String effectName) {
//        List<LogModel> result = new ArrayList<>();
//        for (LogModel log : logs) {
//            if (log.getEffectName().equals(effectName)) {
//                result.add(log);
//            }
//        }
//        return result;
//
//    }
//
//    public void clearLogs() {
//        logs.clear();
//        try (PrintWriter w = new PrintWriter(LOG_FILE_PATH)) {
//            // Empty file
//        } catch (FileNotFoundException e) {
//            e.printStackTrace();
//        }
//    }
//
//    public List<LogModel> getLogsBetweenTimestamps(LocalDateTime startTime, LocalDateTime endTime) {
//        //return new ArrayList<LogModel>();
//        List<LogModel> result = new ArrayList<>();
//        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
//        for (LogModel log : logs) {
//            try {
//                LocalDateTime logTimestamp = LocalDateTime.parse(log.getTimestamp(), formatter);
//                if (logTimestamp.isEqual(startTime) || (logTimestamp.isAfter(startTime) && logTimestamp.isBefore(endTime))) {
//                    result.add(log);
//                }
//            } catch (DateTimeParseException e) {
//                e.printStackTrace();
//            }
//        }
//        return result;
//    }
//
//    private void loadLogs() {
//        //logs = new ArrayList<>();
//
//        try (BufferedReader reader = new BufferedReader(new FileReader(LOG_FILE_PATH))) {
//            String line;
//            while ((line = reader.readLine()) != null) {
//                String[] parts = line.split("\t");
//                if (parts.length == 4) {
//                    String timestamp = parts[0];
//                    String filename = parts[1];
//                    String effectName = parts[2];
//                    String optionValues = parts[3];
//                    LogModel logModel = new LogModel(timestamp, filename, effectName, optionValues);
//                    logs.add(logModel);
//                }
//            }
//        } catch (IOException e) {
//            e.printStackTrace();
//        }
//    }
//    public void shutdownThreadPool() {
//        // Shutdown the thread pool when it's no longer needed
//        threadPool.shutdown();
//    }
//}
//
//
package com.iiitb.imageEffectApplication.service;
import org.springframework.stereotype.Service;
import com.iiitb.imageEffectApplication.model.LogModel;

import java.io.*;
import java.text.SimpleDateFormat;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
@Service
// This class provides logging functionality for an image effect application.
public class LoggingService {
    private static final int THREAD_POOL_SIZE = 5; // Number of threads in the thread pool for asynchronous logging
    private ExecutorService threadPool; // ExecutorService for managing the thread pool
    private static final String LOG_FILE_PATH = "logging.txt"; //log file
    private List<LogModel> logs = new ArrayList<>(); // List to store log entries as LogModel objects

    public LoggingService() { // Constructor initializes the thread pool and loads existing logs from the file
        threadPool = Executors.newFixedThreadPool(THREAD_POOL_SIZE);
        loadLogs();
    }

    // Asynchronously adds a log entry to the log file and updates the in-memory log list
    public void addLog(String fileName, String effectName, String optionValues) {
        threadPool.submit(() -> writeToLogFile(fileName, effectName, optionValues));
    }

    // Writes a log entry to the log file and adds it to the in-memory log list
    private void writeToLogFile(String fileName, String effectName, String optionValues) {
        // Formatting the current timestamp
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        String timestamp = dateFormat.format(new Date());
        try (PrintWriter w = new PrintWriter(new BufferedWriter(new FileWriter(LOG_FILE_PATH, true)))) {
            // Creating a log entry string
            String logEntry = String.format("%s\t%s\t%s\t%s\n", timestamp, fileName, effectName, optionValues);
            w.write(logEntry); // Writing the log entry to the file
            // Creating a LogModel object
            LogModel log = new LogModel(timestamp, fileName, effectName, optionValues);
            logs.add(log); //adding the created LogModel object to the in-memory log list
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // Retrieves all log entries
    public List<LogModel> getAllLogs() {
        return logs;
    }

    // Retrieves log entries for a specific image effect
    public List<LogModel> getLogsByEffect(String effectName) {
        List<LogModel> result = new ArrayList<>();
        for (LogModel log : logs) {
            if (log.getEffectName().equals(effectName)) {
                result.add(log);
            }
        }
        return result;

    }

    // Clears all log entries both in-memory and in the log file
    public void clearLogs() {
        logs.clear();
        try (PrintWriter w = new PrintWriter(LOG_FILE_PATH)) {
            // Empty file
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

    // Retrieves log entries within a specified time range
    public List<LogModel> getLogsBetweenTimestamps(LocalDateTime startTime, LocalDateTime endTime) {
        //return new ArrayList<LogModel>();
        List<LogModel> result = new ArrayList<>();
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        for (LogModel log : logs) {
            try {
                // Parses the timestamp of each log entry
                LocalDateTime logTimestamp = LocalDateTime.parse(log.getTimestamp(), formatter);
                // Checks if the log entry's timestamp is within the specified range
                if (logTimestamp.isEqual(startTime) || (logTimestamp.isAfter(startTime) && logTimestamp.isBefore(endTime))) {
                    result.add(log);
                }
            } catch (DateTimeParseException e) {
                e.printStackTrace();
            }
        }
        return result;
    }

    // Loads existing logs from the log file during initialization
    private void loadLogs() {
        try (BufferedReader reader = new BufferedReader(new FileReader(LOG_FILE_PATH))) {
            String line;
            // Reads each line from the file and creates LogModel objects
            while ((line = reader.readLine()) != null) {
                String[] parts = line.split("\t");
                if (parts.length == 4) {
                    String timestamp = parts[0];
                    String filename = parts[1];
                    String effectName = parts[2];
                    String optionValues = parts[3];
                    LogModel logModel = new LogModel(timestamp, filename, effectName, optionValues);
                    logs.add(logModel);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public void shutdownThreadPool() {
        // Shutdown the thread pool when it's no longer needed
        threadPool.shutdown();
    }
}


