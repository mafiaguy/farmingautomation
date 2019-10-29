package com.example.setup_minor;

public class Cropitems {
    private String nCropName;
    private int nCropImage;

    public Cropitems(String cropName, int cropImage) {
        nCropName = cropName;
        nCropImage = cropImage;
    }

    public String getCropName() {
        return nCropName;
    }

    public int getCropImage() {
        return nCropImage;
    }
}

