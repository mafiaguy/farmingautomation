package com.example.setup_minor;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.ArrayList;

public class CropAdapter extends ArrayAdapter<Cropitems> {
    public CropAdapter(Context context, ArrayList<Cropitems> cropList){
        super(context, 0, cropList);
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        return initView(position, convertView, parent);
    }

    @Override
    public View getDropDownView(int position, View convertView, ViewGroup parent) {
        return initView(position, convertView, parent);
    }

    private  View initView(int position, View convertView, ViewGroup parent){
        if(convertView==null){
            convertView= LayoutInflater.from(getContext()).inflate(
                    R.layout.crop_layout, parent, false
            );
        }

        ImageView imageViewCrop=convertView.findViewById(R.id.image_crop_view);
        TextView textViewName=convertView.findViewById(R.id.crop_name);

        Cropitems currentItem=getItem(position);
        if(currentItem!=null){
            imageViewCrop.setImageResource(currentItem.getCropImage());
            textViewName.setText(currentItem.getCropName());
        }

        return convertView;
    }
}


