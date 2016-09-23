/*	UFUK GÜRBÜZ - 150113058 */

/*public class Native {
        static {
                System.loadLibrary("native_library");
        }
        public static native int sum(int x);

        public static void main(String[] args) {
                sum(3);
        }
}*/

import java.awt.Desktop;
import java.awt.Toolkit;
import java.awt.datatransfer.Clipboard;
import java.awt.datatransfer.StringSelection;
import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.text.Text;
import javafx.scene.control.TextField;
import javafx.scene.control.Label;
import javafx.scene.layout.BorderPane;
import javafx.scene.control.Button;
import javafx.scene.control.RadioButton;
import javafx.scene.control.ToggleGroup;
import javafx.geometry.Pos;
import javafx.geometry.Insets;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import java.io.*;
import java.net.URI;
import java.net.URL;
import java.util.Scanner;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.TextArea;
import javafx.scene.effect.DropShadow;
import javafx.scene.image.ImageView;
import javafx.stage.Modality;
import javafx.scene.layout.VBoxBuilder;
import static javafx.scene.paint.Color.*;
import javafx.scene.text.Font;

public class Native extends Application {
	
	    static {
                System.loadLibrary("native_library");
        }

        public static native void sum(String x);
    
    public static String qFile;
    public  static String takeFilePath;

    @Override
    public void start(Stage primaryStage){
                
        BorderPane borderPane = new BorderPane();
        borderPane.setPadding(new Insets(10,10,10,10));
        
            HBox hbox = new HBox(50);
                ImageView imageView = new ImageView("resim1.png");
                imageView.setFitHeight(150);                                        //Resim1
                imageView.setFitWidth(150);


                VBox vbox = new VBox(10);
                    Font myfont = new Font("Times New Roman",14);
                    Label label = new Label("Please, enter path of file:");
                    label.setFont(myfont);                                          // Path yolu(vbox)
                    TextField textField = new TextField();

                vbox.setPadding(new Insets(30,20,10,20));
                vbox.getChildren().addAll(label,textField);//Vbox

                ImageView imageView2 = new ImageView("resim2.png");
                imageView2.setFitHeight(150);                                       //Resim2
                imageView2.setFitWidth(150);


            hbox.getChildren().addAll(imageView,vbox,imageView2);                                       //Hbox

        //**********************************************************************

            VBox vbox2 = new VBox(10);
                DropShadow ds = new DropShadow();
                ds.setOffsetY(3.0f);
                ds.setColor(BLUE);
                
                Font myfont2 = new Font("Times New Roman",20);
                Label label2 = new Label("<<< QUANTUM VALUE >>>");
                label2.setEffect(ds);
                label2.setFont(myfont2);
                label2.setTextFill(RED);
                label2.setPadding(new Insets(5,0,10,150));
                

                HBox hboxQ = new HBox(15);
                    RadioButton rB1 = new RadioButton("q1");
                    rB1.setSelected(true);
                    RadioButton rB2 = new RadioButton("q2");
                    RadioButton rB3 = new RadioButton("q3");
                    RadioButton rB4 = new RadioButton("q4");
                    RadioButton rB5 = new RadioButton("q5");        // radiobuttons1
                    RadioButton rB6 = new RadioButton("q6");
                    RadioButton rB7 = new RadioButton("q7");
                    RadioButton rB8 = new RadioButton("q8");
                    RadioButton rB9 = new RadioButton("q9");
                    RadioButton rB10 = new RadioButton("q10");
                hboxQ.setPadding(new Insets(10,20,10,20));
                hboxQ.getChildren().addAll(rB1,rB2,rB3,rB4,rB5,rB6,rB7,rB8,rB9,rB10); //hboxQ
                
                
                HBox hboxQ2 = new HBox(8);
                    RadioButton rB11 = new RadioButton("q11");
                    RadioButton rB12 = new RadioButton("q12");
                    RadioButton rB13 = new RadioButton("q13");
                    RadioButton rB14 = new RadioButton("q14");
                    RadioButton rB15 = new RadioButton("q15");      // radiobuttons2
                    RadioButton rB16 = new RadioButton("q16");
                    RadioButton rB17 = new RadioButton("q17");
                    RadioButton rB18 = new RadioButton("q18");
                    RadioButton rB19 = new RadioButton("q19");
                    RadioButton rB20 = new RadioButton("q20");
                hboxQ2.setPadding(new Insets(10,20,10,20));
                hboxQ2.getChildren().addAll(rB11,rB12,rB13,rB14,rB15,rB16,rB17,rB18,rB19,rB20); //hboxQ
            
            vbox2.setPadding(new Insets(30,20,10,20));
            vbox2.getChildren().addAll(label2,hboxQ,hboxQ2);//Vbox
        
        //**********************************************************************
            ToggleGroup group = new ToggleGroup();
                rB1.setToggleGroup(group);
                rB2.setToggleGroup(group);
                rB3.setToggleGroup(group);
                rB4.setToggleGroup(group);
                rB5.setToggleGroup(group);
                rB6.setToggleGroup(group);
                rB7.setToggleGroup(group);
                rB8.setToggleGroup(group);
                rB9.setToggleGroup(group);
                rB10.setToggleGroup(group);
                rB11.setToggleGroup(group);
                rB12.setToggleGroup(group);
                rB13.setToggleGroup(group);
                rB14.setToggleGroup(group);
                rB15.setToggleGroup(group);
                rB16.setToggleGroup(group);
                rB17.setToggleGroup(group);
                rB18.setToggleGroup(group);
                rB19.setToggleGroup(group);
                rB20.setToggleGroup(group);
                
        //**********************************************************************
            
            HBox hboxbtn = new HBox(8);
                Button button = new Button("RUN C !");//Button
                button.setPadding(new Insets(10,20,10,20));
                
                Button button2 = new Button("RUN Python !");//Button
                button2.setPadding(new Insets(10,20,10,20));
                
                Button button3 = new Button("RUN HTML5 !");//Button
                button3.setPadding(new Insets(10,20,10,20));
                
            hboxbtn.setPadding(new Insets(10,20,10,140));
            hboxbtn.getChildren().addAll(button,button2,button3);
            
            textField.setOnAction(e ->{
    			takeFilePath = textField.getCharacters()+"";            // GettingTextFieldCharacters
            	sum(takeFilePath);
    		});
            
            
            
        //******************** RADIOBUTTON ACTIONS *****************************
            rB1.setOnAction(e -> {
                if (rB1.isSelected()) {
                    qFile="dosya//q1.txt";      
                }
            });rB2.setOnAction(e -> {
                if (rB2.isSelected()) {
                    qFile="dosya//q2.txt"; 
                }
            });rB3.setOnAction(e -> {
                if (rB3.isSelected()) {
                    qFile="dosya//q3.txt";
                }
            });rB4.setOnAction(e -> {
                if (rB4.isSelected()) {
                    qFile="dosya//q4.txt";
                }
            });rB5.setOnAction(e -> {
                if (rB1.isSelected()) {
                    qFile="dosya//q5.txt";
                }
            });rB6.setOnAction(e -> {
                if (rB6.isSelected()) {
                    qFile="dosya//q6.txt";
                }
            });rB7.setOnAction(e -> {
                if (rB7.isSelected()) {
                    qFile="dosya//q7.txt";
                }
            });rB8.setOnAction(e -> {
                if (rB8.isSelected()) {
                    qFile="dosya//q8.txt";
                }
            });rB9.setOnAction(e -> {
                if (rB9.isSelected()) {
                    qFile="dosya//q9.txt";
                }
            });rB10.setOnAction(e -> {
                if (rB10.isSelected()) {
                    qFile="dosya//q10.txt";
                }
            });rB11.setOnAction(e -> {
                if (rB11.isSelected()) {
                    qFile="dosya//q11.txt";
                }
            });rB12.setOnAction(e -> {
                if (rB12.isSelected()) {
                    qFile="dosya//q12.txt";
                }
            });rB13.setOnAction(e -> {
                if (rB13.isSelected()) {
                    qFile="dosya//q13.txt";
                }
            });rB14.setOnAction(e -> {
                if (rB14.isSelected()) {
                    qFile="dosya//q14.txt";
                }
            });rB15.setOnAction(e -> {
                if (rB15.isSelected()) {
                    qFile="dosya//q15.txt";
                }
            });rB16.setOnAction(e -> {
                if (rB16.isSelected()) {
                    qFile="dosya//q16.txt";
                }
            });rB17.setOnAction(e -> {
                if (rB17.isSelected()) {
                    qFile="dosya//q17.txt";
                }
            });rB18.setOnAction(e -> {
                if (rB18.isSelected()) {
                    qFile="dosya//q18.txt";
                }
            });rB19.setOnAction(e -> {
                if (rB19.isSelected()) {
                    qFile="dosya//q19.txt";
                }
            });rB20.setOnAction(e -> {
                if (rB20.isSelected()) {
                    qFile="dosya//q20.txt";
                }
            });
            
            //********************* BUTTON1 ACTION *****************************
            button.setOnAction(new EventHandler<ActionEvent>(){
                @Override
                public void handle(ActionEvent e) {
                    try{
                        
                        String yazi = getTextFromFile(qFile);
                        
                        //**************** NEW STAGE ***************************
                        BorderPane qBorderPane = new BorderPane();
                        qBorderPane.setPadding(new Insets(10,10,10,10));
                        
                            TextArea qText = new TextArea();
                            qText.setFont(new Font("Serif", 14));
                            qText.setWrapText(true);
                            qText.setEditable(false);
                            qText.setText(yazi);
                        
                            
                        qBorderPane.setCenter(qText);
                        
                        Scene qScene = new Scene(qBorderPane, 800, 360);
                    
                        Stage qStage = new Stage();  
                        qStage.setTitle(qFile); // Set the stage title
                        qStage.setScene(qScene); // Place the scene in the stage
                        qStage.show(); // Display the stage
                        
                   }
                    catch(Exception a){
                        Stage dialogStage = new Stage();
                        dialogStage.initModality(Modality.WINDOW_MODAL);
                        dialogStage.setScene(new Scene(VBoxBuilder.create().children(new Text("Not Found C File !")).alignment(Pos.CENTER).padding(new Insets(5)).build(),200,100));
                        dialogStage.show();
		    }
            }});
            
            //********************* BUTTON2 ACTION *****************************
            button2.setOnAction(new EventHandler<ActionEvent>(){
                @Override
                public void handle(ActionEvent ee) {
                   try{
                        ProcessBuilder pb = new ProcessBuilder("python","Native.py","dosya//pythonFile.txt");
                        Process p = pb.start();  
                   }
                    catch(Exception b){
                        Stage dialogStage = new Stage();
                        dialogStage.initModality(Modality.WINDOW_MODAL);
                        dialogStage.setScene(new Scene(VBoxBuilder.create().children(new Text("Not Found Python File !")).alignment(Pos.CENTER).padding(new Insets(5)).build(),200,100));
                        dialogStage.show();
		    }
            }});
            
                        //********************* BUTTON2 ACTION *****************************
            button3.setOnAction(new EventHandler<ActionEvent>(){
                @Override
                public void handle(ActionEvent eee) {
                   try{
                       methodHTML("dosya//pythonFile.txt");
                       File htmlFile = new File("Native.html");
					   Desktop.getDesktop().browse(htmlFile.toURI());
                   }
                    catch(Exception c){
                        Stage dialogStage = new Stage();
                        dialogStage.initModality(Modality.WINDOW_MODAL);
                        dialogStage.setScene(new Scene(VBoxBuilder.create().children(new Text("Not Found HTML File !")).alignment(Pos.CENTER).padding(new Insets(5)).build(),200,100));
                        dialogStage.show();
		    }
            }});
            
                   
            
        borderPane.setTop(hbox);
        borderPane.setCenter(vbox2);
        borderPane.setBottom(hboxbtn);
                  
        Scene scene = new Scene(borderPane,600,400);
        primaryStage.setScene(scene);
        primaryStage.show();
    }
    
    public static String getTextFromFile(String fileName) throws IOException{
        File file = new File(fileName);
        BufferedReader reader = null;
        reader = new BufferedReader(new FileReader(file));
        int i=0;
        String satir = reader.readLine();
  		String metin="";
            while (satir!=null) {
            	metin += satir+"\n";
                satir = reader.readLine();
            }

            return metin;
    }
    
    public static void methodHTML(String pythonFile) throws IOException{
        File file = new File(pythonFile);
        BufferedReader reader = null;
        reader = new BufferedReader(new FileReader(file));
        int i=0;
        String satir = reader.readLine();
  		String metin="";
        
        while (satir!=null) {
            metin += "\t\t"+satir+"\n";
            satir = reader.readLine();
        }
            
		StringBuilder sb = new StringBuilder();
    	
        sb.append("<html style=\"background-color:#66FFFF;\">");
    	  sb.append("<head>");
    	    sb.append("<title>HTML Results");
    	    sb.append("</title>");
    	  sb.append("</head>");
    	  sb.append("<body>");
    	    sb.append("<h1 style=\"color:#CC0000;text-shadow:2px 2px 5px #00CC00;margin:10px 30px 10px 480px\">Average Waiting Time Results</h1>");
    	    sb.append("<pre>");
    	      sb.append("<p style=\"padding:15px;margin:10px 250px 10px 280px;border:2px solid #CC0066\">");
    	        sb.append(metin);
    	      sb.append("</p>");
    	    sb.append("</pre>");
    	  sb.append("</body>");
    	sb.append("</html>");
    	
    	FileWriter fstream = new FileWriter("Native.html");
    	BufferedWriter out = new BufferedWriter(fstream);
    	out.write(sb.toString());
        out.close();
    }
    
    
    public static void main(String [] args){
         
        launch(args);
    }
}