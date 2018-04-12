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
	
	/*获得文本框*/
	public void click_pop(View v){
	 	new AlertDialog.Builder(this)
	// 	.setTitle("请输入")//标题
	// 	.setIcon(android.R.drawable.ic_dialog_info)//标题旁边图片
	 	.setView(new EditText(this))//文本框
	 	.setPositiveButton("发送", null)//按钮
	 	.setNegativeButton("取消", null)//按钮
	 	.show();
		
	}
	
	/*退出*/
	public void click_quit(View v){
		finish();
	}

}
