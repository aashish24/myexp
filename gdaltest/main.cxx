
#include <fstream>
#include <iostream>
#include <sstream>

#include <gdal_priv.h>
#include <cpl_vsi.h>

int main(int argc, char** argv)
{
  std::cout << "Reading file " << argv[1] << std::endl;


  std::ifstream file (argv[1], std::ios::in|std::ios::binary|std::ios::ate);
  if (file.is_open())
  {
    std::ifstream::pos_type size = file.tellg();
    char* raw_data = new char [size];
    file.seekg (0, std::ios::beg);
    file.read (raw_data, size);
    file.close();

    // Initialize all variables
    GDALDataset* gdal_data = NULL;

    // Enable all drivers
    GDALAllRegister();

    // Create virtual file
    std::string filename;
    std::ostringstream out;
    out << "/vsimem/tmp_" << &file;
    filename = out.str();

    VSILFILE *fpTemp = VSIFileFromMemBuffer(filename.c_str(),
      (GByte*)raw_data, size, FALSE);

    gdal_data = (GDALDataset*) GDALOpen(
      filename.c_str(), GA_ReadOnly);

    // Read the data now
    //
    //////////////////////////////////////////////////////////////////////////

    // Placeholder for the read data
    std::vector<GByte*> rawImageData;

    // Possible bands
    GDALRasterBand* redBand = 0;
    GDALRasterBand* greenBand = 0;
    GDALRasterBand* blueBand = 0;
    GDALRasterBand* alphaBand = 0;
    GDALRasterBand* greyBand = 0;
    GDALDataType target_data_type = GDT_Unknown;

    int np = gdal_data->GetRasterCount(); // no of planes
    int ni = gdal_data->GetRasterXSize(); // width
    int nj = gdal_data->GetRasterYSize(); // height
    int i0 = 0; // start x pos
    int j0= 0; // start y pos
    int nbpp; // No of bytes per pixel
    GDALDataType data_type;

    for (int i = 1; i <= np; ++i)
      {
      GDALRasterBand* rasterBand = gdal_data->GetRasterBand(i);
      if (nbpp == 0)
        {
        data_type = rasterBand->GetRasterDataType();
        switch (data_type)
          {
          case (GDT_Byte): nbpp = 1; break;
          case (GDT_UInt16): nbpp = 2; break;
          case (GDT_Int16): nbpp = 2; break;
          case (GDT_UInt32): nbpp = 4; break;
          case (GDT_Int32): nbpp = 4; break;
          case (GDT_Float32): nbpp = 4; break;
          case (GDT_Float64): nbpp = 8; break;
          default: nbpp = 0; break;
          }
        }
      }

    for (int i = 1; i <= np; ++i)
    {
      GDALRasterBand* rasterBand = gdal_data->GetRasterBand(i);

      if(target_data_type == GDT_Unknown)
      {
        target_data_type = rasterBand->GetRasterDataType();
      }

      if ((rasterBand->GetColorInterpretation() == GCI_RedBand) ||
          (rasterBand->GetColorInterpretation() == GCI_YCbCr_YBand))
      {
        redBand = rasterBand;
      }
      else if ((rasterBand->GetColorInterpretation() == GCI_GreenBand) ||
               (rasterBand->GetColorInterpretation() == GCI_YCbCr_CbBand))
      {
        greenBand = rasterBand;
      }
      else if ((rasterBand->GetColorInterpretation() == GCI_BlueBand) ||
               (rasterBand->GetColorInterpretation() == GCI_YCbCr_CrBand))
      {
        blueBand = rasterBand;
      }
      else if (rasterBand->GetColorInterpretation() == GCI_AlphaBand)
      {
        alphaBand = rasterBand;
      }
      else if (rasterBand->GetColorInterpretation() == GCI_GrayIndex)
      {
        greyBand = rasterBand;
      }
    }

    int dest_width = static_cast<int>(ni);
    int dest_height = static_cast<int>(nj);

    // GDAL top left is at 0,0
    const int window_x = static_cast<int>(i0);
    const int window_y = static_cast<int>(j0);
    const int window_width = dest_width;
    const int window_height = dest_height;

    rawImageData.resize(np * dest_width * dest_height * nbpp);

    int pixel_space = static_cast<int>(nbpp);
    int line_space = dest_width * pixel_space;
    int band_space = dest_width * dest_height * pixel_space;
    CPLErr err;

    // TODO: Support other band types
    if (redBand && greenBand && blueBand)
    {
      if (alphaBand)
      {
        err = redBand->RasterIO(
                GF_Read, window_x, window_y,  window_width, window_height,
                (void*)((GByte*)&rawImageData[0] + 0 * band_space), dest_width, dest_height,
                target_data_type, pixel_space, line_space);
        err = greenBand->RasterIO(
                GF_Read, window_x, window_y,  window_width, window_height,
                (void*)((GByte*)&rawImageData[0] + 1 * band_space), dest_width, dest_height,
                target_data_type, pixel_space, line_space);
        err = blueBand->RasterIO(
                GF_Read, window_x, window_y,  window_width, window_height,
                (void*)((GByte*)&rawImageData[0] + 2 * band_space), dest_width, dest_height,
                target_data_type, pixel_space, line_space);
        err = alphaBand->RasterIO(
                GF_Read, window_x, window_y,  window_width, window_height,
                (void*)((GByte*)&rawImageData[0] + 3 * band_space), dest_width, dest_height,
                target_data_type, pixel_space, line_space);
      }
      else
      {
        err = redBand->RasterIO(
                GF_Read, window_x, window_y,  window_width, window_height,
                (void*)((GByte*)&rawImageData[0] + 0 * band_space), dest_width, dest_height,
                target_data_type, 0, 0);
        err = greenBand->RasterIO(GF_Read, window_x, window_y,  window_width, window_height,
               (void*)((GByte*)&rawImageData[0] + 1 * band_space), dest_width, dest_height,
                target_data_type, 0,0);
        err = blueBand->RasterIO(GF_Read, window_x, window_y,  window_width, window_height,
                (void*)((GByte*)&rawImageData[0] + 2 * band_space), dest_width, dest_height,
                target_data_type, 0,0);
      }
    }
    else if (greyBand)
    {
      if (alphaBand)
      {
        // Luminance alpha
        err = greyBand->RasterIO(
                GF_Read, window_x, window_y,  window_width, window_height,
                (void*)((GByte*)&rawImageData[0] + 0 * band_space), dest_width, dest_height,
                target_data_type, pixel_space, line_space);
        err =  alphaBand->RasterIO(
                 GF_Read, window_x, window_y,  window_width, window_height,
                 (void*)((GByte*)&rawImageData[0] + 1 * band_space), dest_width, dest_height,
                 target_data_type, pixel_space, line_space);
      }
      else
      {
        // Luminance
        err = greyBand->RasterIO(
                GF_Read, window_x, window_y, window_width, window_height,
                (void*)((GByte*)&rawImageData[0] + 0 * band_space), dest_width, dest_height,
                target_data_type, pixel_space, line_space);
      }
    }
    else
    {
      std::cerr << "Unknown raster band type \n";
      return NULL;
    }

    VSIFCloseL(fpTemp);
    VSIUnlink(filename.c_str());

    // Write the data out
    const char *pszFormat = "GTiff";
    GDALDriver *poDriver;
    GDALRasterBand  *poBand;
    poDriver = GetGDALDriverManager()->GetDriverByName(pszFormat);

    GDALDataset *poDstDS;
    char **papszOptions = NULL;

    poDstDS = poDriver->Create( "/tmp/gdaltest.png", dest_width, dest_height, 1, GDT_Byte,
                                papszOptions );

    poBand = poDstDS->GetRasterBand(1);
    poBand->RasterIO( GF_Write, 0, 0, dest_width, dest_height,
                      &rawImageData[0], dest_width, dest_height, GDT_Byte, pixel_space, line_space );

    /* Once we're done, close properly the dataset */
    GDALClose( (GDALDatasetH) poDstDS );
  }
}

