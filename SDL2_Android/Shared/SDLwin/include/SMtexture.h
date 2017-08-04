#pragma once
#include <SDLGL.h>

class SMtexture
{
public:

	enum Format
	{
		FORMAT_UNDEFINED,       //!< Format is undefined.

		RGB_332,    //!< Unpalettised 8-bit.
		BGR_332,    //!< Unpalettised 8-bit.


		RGB_565,    //!< Unpalettised 16-bit, no alpha.
		BGR_565,    //!< Unpalettised 16-bit, no alpha.


		RGBA_4444,  //!< Unpalettised 16-bit, alpha.
		ABGR_4444,  //!< Unpalettised 16-bit, alpha.
		RGBA_5551,  //!< Unpalettised 16-bit, alpha.
		ABGR_1555,  //!< Unpalettised 16-bit, alpha.


		RGB_888,    //!< Unpalettised 24-bit, no alpha.
		BGR_888,    //!< Unpalettised 24-bit, no alpha.


		RGBA_6666,  //!< Unpalettised 24-bit, alpha.
		ABGR_6666,  //!< Unpalettised 24-bit, alpha.


		RGBA_8888,  //!< Unpalettised 32-bit, alpha.
		ABGR_8888,  //!< Unpalettised 32-bit, alpha.
		RGBA_AAA2,  //!< Unpalettised 32-bit, alpha.
		ABGR_2AAA,  //!< Unpalettised 32-bit, alpha.


		PALETTE4_RGB_888,   //!< 16-colour palettised.
		PALETTE4_RGBA_8888, //!< 16-colour palettised.
		PALETTE4_RGB_565,   //!< 16-colour palettised.
		PALETTE4_RGBA_4444, //!< 16-colour palettised.
		PALETTE4_RGBA_5551, //!< 16-colour palettised.
		PALETTE4_ABGR_1555,

		PALETTE8_RGB_888,   //!< 256-colour palettised.
		PALETTE8_RGBA_8888, //!< 256-colour palettised.
		PALETTE8_RGB_565,   //!< 256-colour palettised.
		PALETTE8_RGBA_4444, //!< 256-colour palettised.
		PALETTE8_RGBA_5551, //!< 256-colour palettised.
		PALETTE8_ABGR_1555,

		PALETTE7_ABGR_1555, //!< 32-colour palettised.
		PALETTE6_ABGR_1555, //!< 64-colour palettised.
		PALETTE5_ABGR_1555, //!< 128-colour palettised.

							// PVRTC formats
							PVRTC_2,            //!< PowerVR compressed format.
							PVRTC_4,            //!< PowerVR compressed format.
							ATITC,              //!< ATI compressed format.
							COMPRESSED,         //!< gfx specific compressed format

							PALETTE4_ABGR_4444, //!< 16-colour palettised.
							PALETTE8_ABGR_4444, //!< 256-colour palettised.

							A_8,                //!< Unpalettised 8-bit alpha.

							ETC,                //!< Ericsson compressed format
							ARGB_8888,          //!< Unpalettised 32-bit, alpha.

							PALETTE4_ARGB_8888, //!< 16-colour palettised.
							PALETTE8_ARGB_8888, //!< 256-colour palettised.

							DXT3,               //!< DXT3 compressed format

							PALETTE4_BGR555,        //!< 16-colour palettised.
							PALETTE8_BGR555,        //!< 16-colour palettised.
							A5_PALETTE3_BGR_555,    //!< 8BPP, of which 5 are alpha and 3 are palette index
							A3_PALETTE5_BGR_555,    //!< 8BPP, of which 3 are alpha and 5 are palette index

							PALETTE4_BGR_565,   //!< 16-colour palettised.
							PALETTE4_ABGR_8888, //!< 16-colour palettised.
							PALETTE8_BGR_565,   //!< 256-colour palettised.
							PALETTE8_ABGR_8888, //!< 256-colour palettised.

							DXT1,               //!< DXT1 compressed format
							DXT5,               //!< DXT5 compressed format

							ETC2,               //!< GLES 3.0 mandated formats
							ETC2_A1,            //!< 1bit alpha version
							EAC_R11,            //!< 1 channel version
							EAC_RG11,           //!< 2 channel version

							ASTC,               //!< ASTC compressed format

							DEPTH_16,           //!< 16 bit depth texture (may not be supported)
							DEPTH_32,           //!< 32 bit depth texture (may not be supported)

							FORMAT_MAX,         // (Terminator)
	};

	enum Flags
	{
		// Old CIwTexture flags
		UPLOADED_F = (1 << 0),     //!< This texture has been uploaded.
		NEEDS_SW_TRANSPARENCY_F = (1 << 1),     //!< This texture has (and uses chromakey).
		UPLOAD_ON_LOAD_F = (1 << 2),     //!< Upload this texture as soon as it's been loaded.
		USES_TRANSPARENCY_F = (1 << 3),     //!< Texture uses colour-keying.
		NO_TRANSPARENCY_F = (1 << 4),     //!< Texture doesn't use colour-keying.
		NO_CHROMA_KEY_F = (1 << 5),     //!< Does not convert chroma key values (255, 0 255) to alpha.
		NO_FILTER_F = (1 << 6),     //!< Disable filtering.

		OWNS_TEXELS_F = (1 << 8),     //!< m_Texels (texel data) points to an owned allocation.
		OWNS_PALETTE_F = (1 << 9),     //!< m_Palette (palette data) points to an owned allocation.
		OWNS_PALETTE_CACHE_RGBS_F = (1 << 10),  //!< m_PaletteCacheRGBs points to an owned allocation
		NATIVE_16BIT_F = (1 << 11),    //!< Convert 16bit texture to native when uploading to VRAM
		SHARES_TEXELS_F = (1 << 12),    //!< Uses another texture's texels

		DO_SW_F = (1 << 13),    //!< Perform SW-related functions on this texture
		DO_HW_F = (1 << 14),    //!< Perform HW-related functions on this texture

		KEEP_DATA_AFTER_UPLOAD_F = (1 << 15), //!< Don't delete the texels and palette after upload. Use this for palette animation. Uses no extra memory if software rendering is enabled.
		ANIMATE_UV_F = (1 << 16),    // Animate UVs. USED BY LEGACY CODE ONLY.

		NEVER_SW_F = (1 << 17),    //!< Never upload this texture for SW
		NO_MIPMAPPING_F = (1 << 18),    //!< Disable mipmapping.
		CLAMP_UV_F = (1 << 19),    //!< Clamp (rather than wrap) in U and V

		SKIPPED_MIPMAP_GENERATION = (1 << 20), //!< Record if mip maps should have been generated, but weren't

		CREATE_FOR_3D_API_F = (1 << 21),    //!< For targets which support separate 2D and 3D APIs (e.g. J2ME + JSR-184), create the 3D API image (e.g. JSR-184's Image2D and Texture2D)
		CREATE_FOR_2D_API_F = (1 << 22),    //!< For targets which support separate 2D and 3D APIs (e.g. J2ME + JSR-184), create the 2D API image (e.g. MIDP's Image)

		SHARED_SOURCE_F = (1 << 23),    //!< Other textures share this texture's texels

		CLAMP_UV_SET_F = (1 << 24),    //!< Has HW target been set to clamp?

		DONT_SERIALISE_IMAGE_F = (1 << 25),    //!< Do not save any image data for this texture

		ATTACHED_TO_SURFACE_F = (1 << 26),    //!< It is an error to use a texture that's bound to the active surface
		BOUND_TO_ACTIVE_SURFACE_F = (1 << 27),    //!< It is an error to use a texture that's bound to the active surface
		OWNS_HW_TEXELS_F = (1 << 28),    //!< Does this texture own its HW storage?

		CUBE_MAP_F = (1 << 29),    //!< This texture contains a cube map. The pre-upload texture is a column of cube map faces in the order +ve/-ve x, +ve/-ve y, +ve/-ve z.

		IGNORE_MIPMAP_OFFSET_F = (1 << 30),    //!< This texture will not be affected by the mipmap offset

		ALLOW_LOW_QUALITY_F = (1u << 31),    //!< Indicate low quality compression can be used for this texture
	};

	SMtexture();
	~SMtexture();

	void    LoadFromFile(const char* file);
	//void    CopyFromBuffer(uint16_t w, uint16_t h, Format format, uint16_t pitch, uint8_t* pImageData, uint16_t* pPalette);

	virtual void    Upload();
	void    ChangeTexels(uint8_t* pTexels, Format format);
	//void    RemakeMipmaps();

	inline int32_t GetTexelsMemSize() const
	{
		return size;
	}
	inline uint32_t GetWidth() const { return width; }
	inline uint32_t GetHeight() const { return height; }
	inline uint16_t GetDepth() const { return (uint16_t)bpp; }

	inline uint32_t GetFlags() const { return m_Flags; }
	uint8_t * GetTexels() { return pixels; };
	//void GetTexels(uint8_t * pTexels, Format format) const;

	uint32_t  GetPitch() const
	{
		return pitch;
	}

	//void SetFiltering(bool bOn);
	inline bool GetFiltering() const { return (m_Flags & NO_FILTER_F) == 0; }
	//void SetMipMapping(bool bOn);
	inline bool GetMipMapping() const { return (m_Flags & NO_MIPMAPPING_F) == 0; }
	//void SetClamping(bool bOn);

	void SetModifiable(bool modifiable);

	//void    ReplaceTexture(SMtexture * pTex);
	//void    ChangeTexels(uint8_t * pTexels);



protected:

	uint32_t          m_Flags;        //!< e.g. USES_TRANSPARENCY_F

public:

	uint32_t textureID;
private:
	uint8_t * pixels;
	int bpp;
	int format;
	int width;
	int height;
	int pitch;
	size_t size;

};