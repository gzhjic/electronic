package com.example.kong;

import android.os.Bundle;
import android.app.Activity;
import android.app.AlertDialog;
import android.graphics.Color;
import android.view.Menu;
import android.view.View;
import android.widget.EditText;
import android.widget.MultiAutoCompleteTextView;
import android.widget.TextView;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.demo);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}
	
	/*����ı���*/
	public void click_pop(View v){
	 	new AlertDialog.Builder(this)
	// 	.setTitle("������")//����
	// 	.setIcon(android.R.drawable.ic_dialog_info)//�����Ա�ͼƬ
	 	.setView(new EditText(this))//�ı���
	 	.setPositiveButton("����", null)//��ť
	 	.setNegativeButton("ȡ��", null)//��ť
	 	.show();
		
	}
	
	/*�˳�*/
	public void click_quit(View v){
		finish();
	}

}
