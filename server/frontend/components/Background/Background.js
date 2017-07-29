import React from 'react';
import styles from './Background.css';

export const Background = ({ children }) => (
	<div className={styles.background}>
		{ children }
	</div>
);

export default Background;
