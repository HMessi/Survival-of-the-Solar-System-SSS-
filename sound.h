
//! Sound stuff
// gw_sound.h
// V1.0
// Header file for the gwin base library

#ifndef LIB_SOUND_H
#define LIB_SOUND_H

class GSound;

/**
  * A tiny stub class used for sound positioning
  *
  * @see GSound
  */
struct GPosition
{
	float x, y, z;
};

namespace GSoundFactory
{
	GSound * zero(int len);
	GSound * sine(double freq, int len);
	GSound * wnoise(int len);
};

/**
  * Represents a pre-recorded sound file
  *
  * GSample is used to load large sound files from disc (WAV files or MP3s, for example). To
  * load a sample in memory, use the \a GSound::loadSound method.
  */
class GSample
{
	friend class GSound;
public:
	~GSample();

	/**
	  * Start playing a sound.
	  *
	  * Begins playback of the current sample. The sample plays in the
	  * background (asynchronously) and play() returns immediately. You can
	  * use isPlaying() to wait for termination.
	  */
	void play();

	/**
	  * Stops sound playback
	  *
	  * Stops an already playing sound. Note that it also purges the sound buffers,
	  * so if you want to resume the sound later it won't be possible - for that, see \a pause.
	  */
	void stop();

	/**
	  * Pauses sound playback
	  *
	  * Pauses a playing sound. Use play() to resume it again.
	  */
	void pause();

	/**
	  * Query if the sound is playing
	  *
	  * Return true if the sound is playing, or false if it isn't.
	  */
	bool isPlaying();

	/**
	  * Wait for a sound to stop playing.
	  *
	  * Waits for sound playback to finish.
	  */
	void wait();

	/**
	  * Sets the position of the sound in space.
	  *
	  * Makes the sound appear to come from position \a pos. The users
	  * 'head' is assumed to be at (0, 0, 0), so:
	  *
	  * '-1, 0, 0' is directly left
	  *
	  * '1, 0, 0' is directly right
	  *
	  * '1, 1, 0' is forward and right
	  *
	  * and so on. You can go as many units away from the origin as you like, but
	  * in practice, values < 10 seem to work well (10 is very quiet).
	  */
	void setPosition(GPosition pos);

	/**
	  * @todo document me
	  */
	void setDistance(float dmin, float dmax);

	/**
	  * Return the minimum and maximum hearable distances
	  */
	void getDistance(float &dmin, float &dmax);


	void *getChannel();

private:
	GSample(GSound *, const char *name, bool loop=false);

	GSample(const GSample &);
	GSample &operator= (const GSample &);
	GSound *master;
	void *sample;
	void *channel;
};

/**
  * A sample is a sound file. Normally, if you want to play a sound more than once, you
  * would use a sample. Samples are read from disc directly into memory.
  *
  * A stream, on the other hand, is read one chunk at a time. This is much better for very
  * large files which can't fit into memory.
  */
class GSound
{
public:
	GSound();
	GSound(short *, int slen);
	~GSound();

	GError play();
    GStream *streamSound(const char *name, bool loop=false);

	/**
	  * Load a sound sample into memory.
	  *
	  * Loads the file with name 'name'. You can make the sound loop by passing
	  * 'true' for the loop parameter.
	  *
	  * Note that if you have enable 3D sound support, all sound samples must be in mono. MP3
	  * are automatically converted to mono if needed, but WAV/other files are not.
	  *
	  * The function returns a GSample structure. To play the sound, call the play() function.
	  *
	  * You are given ownership of the GSample ; it is your responsibility to delete it when you
	  * no longer require it.
	  */
	GError load(std::string fpath, bool loop=false);

	GError loadBuffer(short *buf, int slen);

	GError stop();

	/*
	 * Returns TRUE if 3D is supported.
	 *
	 * Returns TRUE if 3D is supported and active on the current device.
	 */
	bool is3D();

	// dump sound file to disk
	GError saveSound(std::string fpath, std::string format="raw");

	// Wait for channel to terminate
	GError wait();
private:
	GSound & operator= (const GSound &);
	int channel;
	void *chunkptr;

	// used for a temp copy of the buffer (if we need one)
	void *rawptr;
	bool loop;

	bool threed;

};

#endif
