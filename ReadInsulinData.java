package guiPractice;



import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;



public class ReadInsulinData {
	
	private String inputFile;
	public void setInputFile(String iFile) {
		inputFile = iFile;
	}
	
	public void sumData() throws FileNotFoundException {
		double sum = 0;
		FileInputStream f1 = new FileInputStream(new File(inputFile));
		HSSFWorkbook w;
		try {
			w = new HSSFWorkbook(f1);
			HSSFSheet sh1 = w.getSheetAt(0);
			HSSFRow row;
			for(int r = 1; r < sh1.getLastRowNum(); r++) {
				row = sh1.getRow(r);
				if(row != null) {
					HSSFCell c1 = row.getCell(1);
					HSSFCell c2 = row.getCell(12);
					if(c1 != null) {
						 double d1 = c1.getNumericCellValue();
						 if(d1 >= 43065 && d1 <= 43066) {
							 if(c2 != null) {
								 sum = sum + c2.getNumericCellValue();
							 }
						 }
					}
				}
			}
			System.out.println(sum);
		}
		catch(Exception e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) throws FileNotFoundException {
		// TODO Auto-generated method stub
		ReadInsulinData rid = new ReadInsulinData();
		rid.setInputFile("D:\\Insulin Pump Data.xls");
		rid.sumData();
	}

}
