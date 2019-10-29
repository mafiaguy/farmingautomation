package com.example.setup_minor;

import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity implements AdapterView.OnItemSelectedListener {
    private ArrayList<Cropitems> nCropList;
    private CropAdapter nAdapter;
    private Button button;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        button=(Button) findViewById(R.id.button);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                openactivity2();
            }
        });

        Spinner spinner = findViewById(R.id.spinner_State);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this, R.array.country_arrays, android.R.layout.simple_spinner_item);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(adapter);
        spinner.setOnItemSelectedListener(this);


        initList();

        Spinner spinnerCrops = findViewById(R.id.spinner_crop);

        nAdapter = new CropAdapter(this, nCropList);
        spinnerCrops.setAdapter(nAdapter);

        spinnerCrops.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                Cropitems clickedItem = (Cropitems) parent.getItemAtPosition(position);
                String clickedCropName = clickedItem.getCropName();
                if(position>0){
                    Toast.makeText(MainActivity.this, "Crop: "+clickedCropName, Toast.LENGTH_SHORT).show();
                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });

    }
    @Override
    public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
        String text = parent.getItemAtPosition(position).toString();
        Toast.makeText(parent.getContext(), "State: "+text, Toast.LENGTH_SHORT).show();
    }
    @Override
    public void onNothingSelected(AdapterView<?> parent) {
    }

    private void initList() {
        nCropList = new ArrayList<>();
        nCropList.add(new Cropitems("Tomato", R.drawable.tomato));
        nCropList.add(new Cropitems("Mushroom", R.drawable.mushroom));
        nCropList.add(new Cropitems("Peas", R.drawable.peas));
        nCropList.add(new Cropitems("Mustard", R.drawable.mustard));

    }

    public void openactivity2(){
        Intent intent=new Intent(this, Wifi.class);
        startActivity(intent);
    }
}